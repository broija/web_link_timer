/*!
    Copyright 2016 Broija

    This file is part of web_video_timer app.

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

#ifndef WVT_WEBLINKMANAGER_H
#define WVT_WEBLINKMANAGER_H

#include "keyboardinputsender.h"

/*! \todo
 *  - New class web browser manager:
 *    - get Window Class (Firefox : window class), and FindWindow second parameter.
 *    - get new tab shortcut
 *    - get address bar focus shortcut
 *  - New method: set web browser. */
class WebLinkManager
{
public:
    WebLinkManager();
    WebLinkManager(std::string _filename);///< Constructor loading web links from a config file.

    void loadConfigFile(std::string _filename);///< Loads web links from a config file.

    bool availableLinks();///< Returns true if there is still links to work with in the queue.

    void launchList();///< Starts playing the links from the beginning of the queue.
    void stop();///< Stops launching the links.

    void next();///< Launch next link.

    void waitNext();///< Waits until the end of the current link.

protected:
    using Modifier = KeyboardInputSender::Modifier;

    struct WebLink
    {
        using Duration = std::uint32_t;
        using Url = std::string;

        Duration duration;
        Url url;
    };//WebLink

    void addWebLink(WebLink::Duration _duration, WebLink::Url _url);

    void launch();

    bool m_firstLink = true;
    std::size_t m_index;//Link list index

    KeyboardInputSender m_kbInpSender;

    std::vector<WebLink> m_webLinks;
    std::size_t m_webLinkCount;
};//WebLinkManager

#endif // WVT_WEBLINKMANAGER_H
