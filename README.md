# Talk Calendar

Talk Calendar is a personal desktop calendar for Linux which can read out calendar events.

The Calendar GUI has been developed using C and [GTK4](https://docs.gtk.org/gtk4/) for GTK desktops (XFCE, GNOME, Ubuntu Desktop, Cinnamon etc.). 

A screenshot of Talk Calendar is shown below. 

![](talkcalendar.png)

## Core Features

* built with C and GTK4 for GTK based desktops
* month-view calendar
* export and import iCalendar files (backup and restore)
* calendar tools such as calculate Easter and search for events
* built-in speech synthesizer
* Sqlite3 database used to store events

## Install

A pre-built executable binary of the latest version of Talk Calendar for x86 Debian Trixie GTK4 desktops is available and can be downloaded from the binary directory. This have been built using C and GTK 4.18 and tested using Debian Trixie with the [XFCE](https://xfce.org/) desktop. Once downloaded and unzipped make sure that Talk Calendar has executable permissions before running. To change permissions and run Talk Calendar from the terminal use the commands below.
```
chmod +x talkcalendar
./talkcalendar
```
Alternatively you can use the bash installer found in the binary directory. Just run the terminal command below to install Talk Calendar locally.
```
./install-talkcalendar.sh 
```

## Calendar Interface

Talk Calendar uses a month view calendar with a bottom panel to display day events when a day is selected. To create a new event select a day on the calendar and  select the "new event" menu item of press Ctrl+N. To edit an event, select it in day view panel and then select the "edit event" menu item o Ctrl+E . Likewise to delete an event select it in the day view panel and use the "delete event" menu item or the DELETE key. 

Use the File->Export menu item to export a calendar as an iCalendar file for backup purposes. These typically use the file extension ".ical" or ".ics". The [iCalendar standard](https://icalendar.org/) is an open standard for exchanging calendar and scheduling information between users and computers.  An icalendar file is a plain text file and so can be viewed and modified using a standard text editor. 

Pressing F1 invokes the information window which can also be selected from the menu using the Help->Information menu item. The information window shows the keyboard shortcuts, how many records are in the calendar database and the Sqlite version being used on the system. The About dialog displays the Talk Calendar version number.

Press the spacebar to speak events for the selected day. Press the T-key to speak the current time. Some Talk Calendar screenshot are shown below.

### New Event
![](talkcalendar-new-event.png)

### Preferences
![](talkcalendar-preferences.png)

### Calculate Easter
![](talkcalendar-easter.png)

### Search
![](talkcalendar-search.png)

### Information (F1)
![](talkcalendar-info.png)


### Events Database

Events are stored in an [Sqlite](https://www.sqlite.org/index.html) database. SQLite is a small, fast and full-featured SQL database engine written in C. 

### Export and Import iCalendar Files

Talk Calendar allows a personal calendar to be exported as an iCalendar file. These typically use the file extension ".ical" or ".ics". The [iCalendar standard](https://icalendar.org/) is an open standard for exchanging calendar and scheduling information between users and computers.  An icalendar file is a plain text file and so can be modified using a standard text editor. 

You should backup your events by using the File->Export menu item which by default will create an "talkcalendar.ical" file but the name can be changed. A file chooser dialog is used to allow the file to be located in a chosen directory

### Recurring Events

The only recurring event type that is currently supported by Talk Calendar is yearly. This is required for events such as birthdays and anniversaries. The parser uses icalendar [RRULE](https://icalendar.org/iCalendar-RFC-5545/3-8-5-3-recurrence-rule.html) to determine if an event is yearly (e.g. birthday).

## Updating

To update from a previous version of Talk Calendar export the current calendar to an ical file and then import it into the new version of Talk Calendar. Always keep a backup copy of the Talk Calendar database called talkcalendar.db.

## Speech Synthesis

Talk Calendar uses it own internal speech synthesizer engine. It is a lightweight G2P speech engine coded from scratch. You can find out more about how I developed this speech engine [here](https://github.com/crispinprojects/speak).

## Installer

The bash script installer can be used to install talk Calendar locally in the directory ./local/bin. To install Talk Calendar just run the terminal command below.
```
./install-talkcalendar.sh 
```
To uninstall Talk Calendar run:
```
uninstall-talkcalendar.sh
```

### Building on Debian 13 and Ubuntu 24.04 (x86 Hardware)

To build Talk Calendar from source you need the gcc compiler, GTK4, GLIB, and SQLITE development libraries. You need to install the following packages.

Talk Calendar has been developed using Debian Trixie and the XFCE desktop (X11 backend). However, I have tested it with the GNOME desktop (Wayland) and it works fine.

```
sudo apt install build-essential
sudo apt install libgtk-4-dev
sudo apt install libasound2-dev
sudo apt install sqlite3
sudo apt install libsqlite3-dev
```
To check the installed Sqlite 3 version use the command below.

```
sqlite3 --version
```

To determine which version of GTK4 is running on a Ubuntu/Debian system use the following terminal command.

```
gtk4-launch --version
```
or
```
dpkg -l | grep libgtk*
```
Use the MAKEFILE to compile Talk Calendar. Just run "make" inside the source code folder.

```
make
```

To run Talk Calendar from the terminal use

```
./talkcalendar
```
### Building on Fedora

With Fedora you need to install the following packages to compile Talk Calendar.

```
sudo dnf install gcc make
sudo dnf install gtk4-devel
sudo dnf install gtk4-devel-docs
sudo dnf install glib-devel
sudo dnf install alsa-lib-devel
sudo dnf install sqlite-devel
```

To check the installed Sqlite 3 version use the command below.

```
sqlite3 --version
```

To determine which version of GTK4 is running on a Ubuntu/Debian system use the following terminal command.

```
gtk4-launch --version
```
or

```
dnf list gtk4-devel
```

## Advanced

### How to check which GTK4 libraries installed

```
apt list --installed "libgtk-4*"
```
On my Debian XFCE system I get the following.
```
libgtk-4-1/stable,now 4.18.6+ds-2 amd64 [installed,automatic]
libgtk-4-bin/stable,now 4.18.6+ds-2 amd64 [installed,automatic]
libgtk-4-common/stable,now 4.18.6+ds-2 all [installed,automatic]
libgtk-4-dev/stable,now 4.18.6+ds-2 amd64 [installed]
libgtk-4-media-gstreamer/stable,now 4.18.6+ds-2 amd64 [installed,automatic]
```
Make sure you have all of these to run Talk calendar.

###  GtkCalendar gtk_calendar_mark_day may fail on GNOME but works on XFCE?

The function gtk_calendar_mark_day may fail because of a major layout architecture difference between X11 (XFCE) and Wayland (GNOME) environments. 

The gtk_calendar_mark_day only applies the visual CSS marker to the GtkCalendar internal date grid if the widget is realised (meaning it has allocated physical screen space and drawn its sub-nodes).

* On XFCE (X11 Backend): The display pipeline forces synchronous window mapping. When you create the window, the widgets build their layout almost instantly before the code processes the next lines. The calendar exists structurally, so gtk_calendar_mark_day succeeds.

* On GNOME (Wayland Backend): Wayland uses completely asynchronous window configuration. When gtk_window_present is called, the window and its internal nodes are scheduled to draw, but they are not created instantly. If you call gtk_calendar_mark_day immediately after creating the widget, the calendar’s internal day sub-nodes do not exist yet, causing the call to be silently ignored.

I have attempted to fix this rendering bug across all desktop environments by delaying the gtk_calendar_mark_day function until after the calendar widget emits its map or realise signal. I do not think this issue is a libawaita problem but I could be wrong.

### Libadwaita

To check for libadwaita on Debian use:

```
dpkg -l | grep libadwaita
```
This gives:
```
gir1.2-adw-1:amd64  GObject introspection files for libadwaita
libadwaita-1-0:amd64  (the core runtime package)
```
Libadwaita is not used by XFCE (X11). XFCE is built on GTK3 and handles window decorations and global themes via X11 (xfwm4) using the selected XFCE theme. If you run a standard, vanilla GTK4 application (like Talk Calendar), it will attempt to respect the XFCE design settings.

An application explicitly built with libadwaita (GNOME Text Editor) completely bypasses XFCE and X11 theming protocols. Libadwaita forces its own hardcoded GNOME stylesheet ("Adwaita") and layout onto the window canvas. Because libadwaita overrides client-side decorations, running a libadwaita app under XFCE (X11) can result in a broken visual layout. This is the main reason why I have developed Talk Calendar as a generic GTK4 application without libadwaita. I use and test Talk Calendar using Debian Trixie with Xfce. Debian Trixie is the latest stable release of the Debian operating system, featuring Xfce 4.20 as its desktop environment. Xfce is known for being lightweight, fast and can be customised to look like a traditional desktop.

## Versioning

[SemVer](http://semver.org/) is used for versioning. The version number has the form 0.0.0 representing major, minor and bug fix changes.

## Author

* **Alan Crispin** [Github](https://github.com/crispinprojects)

## Project Status

Active and under development.

## Acknowledgements

* [GTK](https://www.gtk.org/)

* GTK is a free and open-source project maintained by GNOME and an active community of contributors. GTK is released under the terms of the [GNU Lesser General Public License version 2.1](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html).

* [GTK4 API](https://docs.gtk.org/gtk4/index.html)

* [GObject API](https://docs.gtk.org/gobject/index.html)

* [Glib API](https://docs.gtk.org/glib/index.html)

* [Gio API](https://docs.gtk.org/gio/index.html)

* [Geany](https://www.geany.org/) is a lightweight source-code editor (version 2 now uses GTK3). [GPL v2 license](https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt)

* [Sqlite](https://www.sqlite.org/index.html) is open source and in the [public domain](https://www.sqlite.org/copyright.html).

* [speech engine](https://github.com/crispinprojects/speak)

* [Debian](https://www.debian.org/)

* [XFCE](https://xfce.org/)

* [Fedora](https://fedoraproject.org/)

* [Ubuntu](https://ubuntu.com/download/desktop)
