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

import org.alljoyn.dashboard.R;
import org.alljoyn.dashboard.ui.util.UIUtil;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.TextView;

public class LicenseActivity extends BaseActivity
{
    public static final String TEXT_RES_ID_EXTRA = "text_res_id";
    public static final String THIRD_PARTY_LICENCE_EXTRA = "show_thirdpartylicences_id";
    public static final String SHOW_LICENCE_EXTRA = "show_license_id";
    private ViewGroup m_licenseLayout = null;

    private TextView m_titleText = null;
    private TextView m_text = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        boolean isTPL=false;
        boolean isLicence=false;
        Intent intent = getIntent();
        Bundle extras=intent.getExtras();
        if (extras != null)
        {
            isTPL = getIntent().getBooleanExtra(THIRD_PARTY_LICENCE_EXTRA, false);
            isLicence = getIntent().getBooleanExtra(SHOW_LICENCE_EXTRA, false);
        }

        m_licenseLayout = (ViewGroup) getLayoutInflater().inflate(R.layout.page_license, null);
        m_titleText = (TextView) m_licenseLayout.findViewById(R.id.navtitleback_title_text);
        m_text = (TextView) m_licenseLayout.findViewById(R.id.license_text);

        setContentView(m_licenseLayout);

        final OnClickListener onBack = new OnClickListener()
        {
            @Override
            public void onClick(View arg0)
            {
                markGoingBack();
                LicenseActivity.this.finish();
            }
        };

        View view = m_licenseLayout.findViewById(R.id.navtitleback_title_block);
        view.setOnClickListener(onBack);

        final int textId = getIntent().getIntExtra(TEXT_RES_ID_EXTRA, 0);

        if (textId > 0)
        {
            m_text.setText(textId);
        }

        if (isTPL)
        {
            m_titleText.setText(R.string.settings_third_party_licenses_title);
            m_text.setText(UIUtil.readRawTextFile(R.raw.thirdpartylicenses, this));
        }
    }
}
