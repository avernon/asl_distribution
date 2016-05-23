/*
* Copyright AllSeen Alliance. All rights reserved.
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
*/
package org.alljoyn.dashboard.ui.activity;


import java.util.Timer;
import java.util.TimerTask;

import org.alljoyn.dashboard.R;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.TextView;

public class HelpActivity extends BaseActivity
{

    public static final String URL_EXTRA = "help_url";

    private class HelloWebViewClient extends WebViewClient
    {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url)
        {
            view.loadUrl(url);
            return true;
        }

        @Override
        public void onPageFinished(WebView view, String url)
        {
            new Timer().schedule(new TimerTask()
            {
                @Override
                public void run() {
                    runOnUiThread(new Runnable()
                    {
                        @Override
                        public void run()
                        {
                            View mProgressBarLayOut=findViewById(R.id.progressbarLayout);
                            mProgressBarLayOut.setVisibility(View.GONE);
                            WebView  mWebView = (WebView) findViewById(R.id.webview);
                            mWebView.setVisibility(View.VISIBLE);
                        }
                    });
                }
            }, 100);
        }
    }

    @SuppressLint("DefaultLocale")
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.page_help);
        TextView m_titleText = (TextView) findViewById(R.id.navtitleback_title_text);
        m_titleText.setText(R.string.help_title);
        View view=findViewById(R.id.navtitleback_title_block);

        view.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View arg0)
            {
                markGoingBack();
                finish();
            }
        });

        Intent intent = getIntent();
        WebView  mWebView = (WebView) findViewById(R.id.webview);

        Bundle extras=intent.getExtras();
        if (extras != null)
        {
            String Url=(String)extras.get(URL_EXTRA);
            if (!Url.toLowerCase().startsWith("http://") && !Url.toLowerCase().startsWith("https://"))
            {
                Url="http://"+Url;
            }

            mWebView.loadUrl(Url);
        }

        mWebView.setWebViewClient(new HelloWebViewClient());
    }

}
