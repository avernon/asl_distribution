#!/usr/bin/env python
# *****************************************************************************
#  Copyright AllSeen Alliance. All rights reserved.
#
#     Contributed by Qualcomm Connected Experiences, Inc.,
#     with authorization from the AllSeen Alliance, Inc.
#     
#     Licensed under the Apache License, Version 2.0 (the "License");
#     you may not use this file except in compliance with the License.
#     You may obtain a copy of the License at
#     
#         http://www.apache.org/licenses/LICENSE-2.0
#     
#     Unless required by applicable law or agreed to in writing, software
#     distributed under the License is distributed on an "AS IS" BASIS,
#     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#     See the License for the specific language governing permissions and
#     limitations under the License.
#     
#     Pursuant to Section 1 of the License, the work of authorship constituting
#     a Work and any Contribution incorporated in the Work shall mean only that
#     Contributor's code submissions authored by that Contributor.  Any rights
#     granted under the License are conditioned upon acceptance of these
#     clarifications.
# *****************************************************************************

import Tkinter as Tk
import socket
import os
import sys

try:
    import win32pipe
    import win32file
    import win32api
    import win32event
    import pywintypes
    import winerror
    import threading
    import Queue
except ImportError:
    if sys.platform == 'win32':
        print "Could not find win32 modules"
        sys.exit(-1)

class Pin(object):
    """Pin abstraction - common functionality across input and output pins"""
    trigger_rising = 1
    trigger_falling = 2

    def __init__(self, val=0, pwm=0):
        #print "val: %s" % val
        self.val = val
        self.pwm = pwm;
        self.trigger = self.trigger_falling

    def setVal(self, val):
        #print "val: %s" % val
        self.val = val

    def getVal(self):
        return self.val

    def setPWM(self, pwm):
        #print "PWM: %s" % pwm
        self.pwm = pwm

    def getPWM(self):
        return self.pwm

    def toggle(self):
        if self.getVal():
            self.setVal(0)
        else:
            self.setVal(1)

    def setTrigger(self, trigger):
        #print "trigger: %s" % trigger
        self.trigger = trigger

    def getTrigger(self):
        return self.trigger

class Led(Pin, Tk.Canvas):
    """Output pin displayed as a colored square"""
    def __init__(self, master, val=1, pwm=255, color="black"):
        Pin.__init__(self, val, pwm)
        Tk.Canvas.__init__(self, master, width=30, height=30)
        self.color = color
        self.draw()

    def draw(self):
        if self.getVal():
            if self.getPWM():
                (r1, g1, b1) = self.winfo_rgb(self.color)
                r1 = (r1*self.getPWM()/65535)
                g1 = (g1*self.getPWM()/65535)
                b1 = (b1*self.getPWM()/65535)
                color = "#%02x%02x%02x" % (r1, g1, b1)
            else:
                color = "black"
        else:
            color = "black"
        self.create_rectangle(0, 0, 30, 30, fill=color)

    def setVal(self, val):
        Pin.setVal(self, val)
        self.draw()

    def setPWM(self, pwm):
        Pin.setPWM(self, pwm)
        self.draw()

class InputPin(Pin, Tk.Checkbutton):
    """Input pin displayed as a check box"""
    def __init__(self, master, val=0, text=""):
        Pin.__init__(self, val, 0)
        self.tkint = Tk.IntVar()
        Tk.Checkbutton.__init__(self, master, text=text, variable=self.tkint)
        self.text = text
        self.tkint.trace('w', self.tkint_cb)
        self.setVal(self.tkint.get())

    def tkint_cb(self, *args):
        #print "%s: %s->%s" % (self.text, self.getVal(), self.tkint.get())
        self.setVal(self.tkint.get())

class InputButton(Pin, Tk.Button):
    """Edge-triggered input button, displayed as a button. Events are sent to the registered server"""
    def __init__(self, master, server, val=0, text=""):
        Pin.__init__(self, val, 0)
        Tk.Button.__init__(self, master, text=text)
        self.server = server
        self.text = text
        self.bind('<Button-1>', self.down_cb)
        self.bind('<ButtonRelease-1>', self.up_cb)

    def down_cb(self, event):
        if self.getTrigger() == Pin.trigger_falling:
            #print "Falling"
            self.server.send_interrupt(self, Pin.trigger_falling)

    def up_cb(self, event):
        if self.getTrigger() == Pin.trigger_rising:
            #print "Rising"
            self.server.send_interrupt(self, Pin.trigger_rising)

def do_pipe_connect(handle, queue):
    """Wait for an incoming connection and report status"""
    try:
        status = win32pipe.ConnectNamedPipe(handle, None)
    except:
        status = -1

    if status == 0:
        queue.put("connected", False)
    else:
        queue.put("disconnected", False)

class Simio(object):
    """
    Overall application object.

    Handles socket IO and GUI organization.
    """

    server_name = "/tmp/ajs_gui"  # Path to socket
    command_len = 4               # Bytes per incoming command
    columns = 4                   # Number of columns in pin display
    pipe_poll_ms = 50             # Milliseconds between pipe reads on Windows
    pipe_quick_poll_ms = 1        # Quick interval for consecutive incoming commands

    def __init__(self, master):
        self.master = master

        frame = Tk.Frame(master)
        frame.grid()

        self.server = None
        self.sock = None
        self.pipe = None
        self.pipe_status = "disconnected"
        self.pipe_connect_thread = None
        self.readbuf = ''

        if sys.platform == 'win32':
            self.pipe_setup()
        else:
            self.server_setup()

        f = frame
        self.pins = [Led(f, color="red"),
                     Led(f, color="green"),
                     Led(f, color="yellow"),
                     Led(f, color="blue"),
                     InputPin(f, text='1'),
                     InputPin(f, text='2'),
                     InputPin(f, text='3'),
                     InputPin(f, text='4'),
                     InputButton(f, self, text='A'),
                     InputButton(f, self, text='B'),
                     InputButton(f, self, text='C'),
                     InputButton(f, self, text='D')]

        for i, pin in enumerate(self.pins):
            pin.grid(row=i/self.columns, column=i%self.columns, padx=20, pady=20)

        self.button = Tk.Button(frame, text="Quit", command=frame.quit)
        self.button.grid(columnspan=self.columns, padx=20, pady=20)

    def pipe_connect(self):
        if self.pipe_status == "connected":
            try:
                win32pipe.DisconnectNamedPipe(self.pipe)
            except:
                pass
            self.pipe_status = "disconnected"

        if self.pipe_status == "disconnected":
            self.pipe_status = "waiting"
            self.pipe_connect_thread = threading.Thread(target=do_pipe_connect,
                                                        args=(self.pipe,self.connectq))
            self.pipe_connect_thread.daemon = True
            self.pipe_connect_thread.start()

    def pipe_setup(self):
        #print "Create pipe: %s" % name
        self.connectq = Queue.Queue()
        self.poll_id = None

        pipename = ("//./pipe" + self.server_name).replace('/', '\\')
        maxinstances = 1
        bufsize = 2048
        timeout = 300
        security = None
        self.pipe = win32pipe.CreateNamedPipe(pipename,
                                              win32pipe.PIPE_ACCESS_DUPLEX,
                                              win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT,
                                              maxinstances, bufsize, bufsize, timeout, security)
        #print "Pipe created: %s" % self.pipe

        self.pipe_connect()
        # Poll for incoming data
        self.pipe_schedule(self.pipe_poll_ms)

    def pipe_schedule(self, ms):
        if self.poll_id is not None:
            self.master.after_cancel(self.poll_id)

        self.poll_id = self.master.after(ms, self.pipe_cb)

    def server_setup(self):
        """Set up incoming socket and listen for connections"""
        self.server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.server.setblocking(0)

        try:
            os.remove(self.server_name)
        except OSError:
            pass

        self.server.bind(self.server_name)
        self.server.listen(1)

        self.master.createfilehandler(self.server, Tk.tkinter.READABLE, self.server_cb)

    def server_shutdown(self):
        """Disable the server socket"""
        if self.server is not None:
            self.master.deletefilehandler(self.server)
        self.server.close()
        self.server = None

    def server_accept(self):
        """Set up communication socket when a client tries to connect"""
        self.sock, address = self.server.accept()
        self.sock.setblocking(0)

        print "Accepted"

        self.master.createfilehandler(self.sock, Tk.tkinter.READABLE, self.sock_cb)

    def sock_recv(self):
        """Handle incoming data and hand off to command processor"""
        data = self.sock.recv(self.command_len)
        #print "sock read: %s" % repr(data)

        if len(data) == 0:
            self.sock_shutdown()
            print "socket closed"

        self.readbuf += data
        while len(self.readbuf) >= self.command_len:
            self.process_command(self.readbuf[:self.command_len])
            self.readbuf = self.readbuf[self.command_len:]

    def sock_shutdown(self):
        """Disable the communication socket"""
        if self.sock is not None:
            self.master.deletefilehandler(self.sock)
        self.sock.close()
        self.sock = None

    def send_interrupt(self, pin, trigger):
        """Issue an interrupt command to the client"""
        if trigger == Pin.trigger_falling:
            edge = 0
        else:
            edge = 1

        self.send_command('i', self.pins.index(pin)+1, edge)

    def send_command(self, command, pin, val):
        """Pack and send a command to the client"""
        data = command + chr(pin) + chr(val)
        print "Send: %s" % repr(data)
        if self.sock:
            self.sock.send(data)
        elif self.pipe and self.pipe_status == "connected":
            try:
                win32file.WriteFile(self.pipe, data, None)
            except:
                print "Write failed, reconnecting"
                self.pipe_connect()

    def process_command(self, command):
        """Parse and perform a single command"""
        print "Command: %s" % repr(command)
        op = command[0]
        pin = ord(command[1])
        val = ord(command[2])
        val2 = ord(command[3])

        if pin >= len(self.pins):
            return

        if op == 'w':
            # Write
            self.pins[pin].setVal(val)
        elif op == 'r':
            # Read
            self.send_command('r', pin, self.pins[pin].getVal())
        elif op == 't':
            # Toggle
            self.pins[pin].toggle()
        elif op == 'i':
            # Interrupt trigger
            self.pins[pin].setTrigger(val)
        elif op == 'p':
            # PWM
            self.pins[pin].setPWM(val2)

    def pipe_cb(self, *args):
        """Callback polling for incoming pipe connection and data"""
        self.poll_id = None
        nextpoll = self.pipe_poll_ms
        if self.pipe_status == "waiting":
            try:
                self.pipe_status = self.connectq.get(False)
            except Queue.Empty:
                pass

        if self.pipe_status != "connected":
            self.pipe_schedule(nextpoll)
            return

        size = None
        while size != 0:
            try:
                data, size, result = win32pipe.PeekNamedPipe(self.pipe, 1024)
            except:
                print "Pipe error, reconnecting"
                self.pipe_connect()
                break

            if size > 0:
                try:
                    hr, data = win32file.ReadFile(self.pipe, size, None)
                    self.readbuf += data
                    nextpoll = self.pipe_quick_poll_ms
                except:
                    print "Read failed, reconnecting"
                    self.pipe_connect()
                    size = 0

        while len(self.readbuf) >= self.command_len:
            self.process_command(self.readbuf[:self.command_len])
            self.readbuf = self.readbuf[self.command_len:]


        self.pipe_schedule(nextpoll)

    def server_cb(self, fno, mask):
        """Callback for when the server socket becomes readable (incoming connection)"""
        if mask & Tk.tkinter.READABLE:
            self.server_accept()

    def sock_cb(self, fno, mask):
        """Callback for when the data socket becomes readable (incoming data)"""
        if mask & Tk.tkinter.READABLE:
            self.sock_recv()

root = Tk.Tk()

simio = Simio(root)

root.mainloop()
try:
    root.destroy()
except:
    pass
