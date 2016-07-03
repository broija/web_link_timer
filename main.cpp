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

#include "weblinkmanager.h"
#include "timer.h"

int main(int _argc, char * _argv[])
{
    Sleep(2000);

    WebLinkManager webLinkManager;

    if (!(_argc > 1))
    {
        std::cout << "No config file specified!" << std::endl;
    }//if (!(_argc > 1))
    else
    {
        webLinkManager.loadConfigFile(_argv[1]);

        webLinkManager.launchList();
    }//if (!(_argc > 1))...else

    return 0;
}//main
