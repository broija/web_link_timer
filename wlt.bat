@ECHO OFF

SET MODE=release

SET QTDIR=D:\Programs\Qt\Qt5.1.0\5.1.0\mingw48_32

SET PATH=%PATH%;%QTDIR%\bin\;%QTDIR%\lib\

%MODE%\web_link_timer.exe "D:/prog/c++/projets/web_link_timer/config/playlist.wvt.ini"