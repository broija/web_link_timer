/*!
    Copyright 2016 Broija

    This file is part of web_link_timer app.

    subdetection is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    subdetection is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with subdetection library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <functional>
#include <fstream>
#include <chrono>
#include <thread>

#include "logger.h"
#include "char_tools.h"

#include "weblinkmanager.h"

WebLinkManager::WebLinkManager():
    m_webLinkCount(0)
{
}//WebLinkManager

//------------------

WebLinkManager::WebLinkManager(std::string _filename):
    WebLinkManager()//delegation
{
    loadConfigFile(_filename);
}//WebLinkManager std::string &

//------------------

void WebLinkManager::loadConfigFile(std::string _filename)
{
    sGlobLogger << "Loading config file: " << _filename << std::endl;

    std::fstream cfgFile(_filename);

    m_webLinks.clear();

    if (!cfgFile.is_open())
    {
        sGlobLogger << "Failed to open config file!" << std::endl;
    }//if (!cfgFile.is_open())
    else
    {
        std::string line;

        std::vector<std::string> linkItems,
                                 timeItems;

        while (std::getline(cfgFile,line))
        {
            linkItems = split(line,';');

            sGlobLogger << "Link items:" << std::endl;

            printStrings(linkItems);

            std::chrono::seconds seconds(0);

            if (linkItems.size() > 1)
            {
                timeItems = split(linkItems.at(1),':');

                sGlobLogger << "Time items:" << std::endl;

                printStrings(timeItems);

                std::chrono::minutes minutes(stoull(timeItems.at(0)));
                seconds = std::chrono::seconds(stoull(timeItems.at(1)));

                seconds += minutes;
            }//if (linkItems.size() > 1)

            addWebLink(seconds.count(),linkItems.at(0));
        }//while (std::getline(file,line))

        cfgFile.close();
    }//if (!file.is_open())...else

    m_webLinkCount = m_webLinks.size();

    sGlobLogger << m_webLinkCount << " link(s) loaded." << std::endl;
}//loadConfigFile

//------------------

bool WebLinkManager::availableLinks()
{
    return m_index < m_webLinkCount;
}//availableLinks

//------------------

void WebLinkManager::launchList()
{
    m_index = 0;

    launch();

    while (availableLinks())
    {
        waitNext();
    }//while (availableLinks())
}//start

//------------------

void WebLinkManager::stop()
{
    m_index = m_webLinks.size();
}//stop

//------------------

void WebLinkManager::next()
{
    ++m_index;

    launch();
}//next

//------------------

void WebLinkManager::waitNext()
{
    if (availableLinks())
    {
        WebLink::Duration duration = m_webLinks.at(m_index).duration;

        sGlobLogger << "Link: " << m_webLinks.at(m_index).url << std::endl;
        sGlobLogger << "Duration: " << duration << std::endl;

        WebLink::Duration count = 0;

        while (count < duration)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            ++count;

            if (!(count %10))
            {
                sGlobLogger << count << std::endl;

                if (!(count %30)) sGlobLogger.currentDatetime();
            }//if (!(count %10))
        }//if (count < duration)

        next();
    }//if (availableLinks())
}//waitNext

//------------------

void WebLinkManager::addWebLink(WebLink::Duration _duration, WebLink::Url _url)
{
    m_webLinks.push_back({_duration,_url});
}//addWebLink

//------------------

void WebLinkManager::launch()
{
    if (availableLinks())
    {
       WebLink weblink = m_webLinks.at(m_index);

       sGlobLogger << '[' << weblink.duration << ',' << weblink.url << "] " << m_index << std::endl;

       HWND webBrowserWinHandle;

#if !defined(WVT_CYGWIN)
       webBrowserWinHandle = FindWindow(L"MozillaWindowClass",NULL);
#else
       webBrowserWinHandle = FindWindow("MozillaWindowClass",NULL);
#endif//!WVT_CYGWIN...else

       if (webBrowserWinHandle == NULL)
       {
           sGlobLogger << "Web browser not found!" << std::endl;
           return;
       }//if (webBrowserWinHandle == NULL)

       if (!SetForegroundWindow(webBrowserWinHandle))
       {
           sGlobLogger << "Couldn't set web browser to foreground!" << std::endl;
           return;
       }//if (!SetForegroundWindow(webBrowserWinHandle))

       //First link to be opened?
       if (m_firstLink)
       {
           //Do nothing
           m_firstLink = false;
       }//if (m_firstLink)
       else
       {
           //Closing previous tab for other links
           m_kbInpSender.appendFx(Modifier::Ctrl,4);
       }//if (m_firstLink)...else

       //Opening new tab
       m_kbInpSender.append(Modifier::Ctrl,'t');

       //Focus on address bar
       m_kbInpSender.append(Modifier::Alt,'d');

       m_kbInpSender.append(weblink.url.c_str());
       m_kbInpSender.appendEnter();

       m_kbInpSender.fire(true);
    }//if (availableLinks())
}//launch

//------------------
