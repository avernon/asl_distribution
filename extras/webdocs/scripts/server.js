#!/usr/bin/env node

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

var express = require('express');
var fs = require('fs');
var os = require('os');
var isBinaryFileSync = require('isbinaryfile');

var app = express();

app.get(/^(.*)$/, function(req, res) {
  var path = 'out/public' + req.params[0];
  var out = "No content at path";
  if (fs.existsSync(path)) {
      stats = fs.statSync(path);
      if (stats.isFile()) {
          console.log("Serving", path);
          if (isBinaryFileSync(path)) {
              out = fs.readFileSync(path);
          } else {
              out = fs.readFileSync(path,'utf8');
          }
          if (path.substring(path.length-4) == '.css') {
            res.contentType('text/css')
          }
          if (path.substring(path.length-4) == '.pdf') {
            res.contentType('application/pdf')
          }

      } else {
          path = path + '/index';
          if (fs.existsSync(path)) {
              console.log("Serving", path);
              out = fs.readFileSync(path, 'utf8');
          } else {
              console.log("Bad path", path);
          }
      }
  } else {
     console.log("Bad path", path);
  }
  res.send(out);
});

var port = 8000;
if (process.argv.length >= 3) { 
    port = process.argv[2];
}

var server = app.listen(port, function() {
    console.log('Started server: http://' + os.hostname() + ':' + port);
});

server.on('error', function(err) {
    if (err.syscall == 'listen' && err.code == 'EADDRINUSE') {
      console.log("Port", port, "already in use")
    } else {
      console.log(err.message);
    }
});

