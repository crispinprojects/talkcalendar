# Talk Calendar

Talk Calendar is a personal desktop calendar for Linux which has some speech capability for reading out dates, times and event details.

Talk Calendar has been developed using C and [GTK4](https://docs.gtk.org/gtk4/) for GTK desktops (Ubuntu Desktop, GNOME, XFCE, Cinnamon etc.). 

A screenshot of Talk Calendar is shown below. 

![](talkcalendar.png)

## Core Features

* built with C and GTK4 for GTK based desktops
* Graphical user interface with month-view calendar with event tooltips
* traditional menu and keybindings 
* event day and today colour preferences 
* dark colour scheme mode
* export and import iCalendar files (backup and restore)
* calendar tools such as calculate Easter and search for events
* Sqlite3 database used to store events

## Pre-built Binary (x86 Intel PCs)

A pre-built 64-bit x86 Talk Calendar executable is available and can be downloaded from the installers directory. Unzip the installer archive file relevant to your distribution which contains the Talk Calendar executable.

Talk Calendar must have executable permissions to execute.  If necessary change Talk Calendar file permissions so that it can run as an executable as shown below.

```
sudo chmod +x talkcalendar
```
Assuming that the GTK4 base libraries are installed the Talk Calendar binary can be run from the terminal using:

```
./talkcalendar
```

## BASH Script Installer

The easiest way to install Talk Calendar is to use the BASH script installer from the terminal. This is found in the installers directory in the download. 

To install Talk Calendar run the installer script as shown below and follow the on-screen instructions.

```
./install-talkcalendar.sh
```

The installer assumes that you are a member of the sudo group and that the GTK4 libraries are installed. If not, go to the build Talk Calendar section below and use the terminal command instructions to install the required packages.

To uninstall Talk Calendar run the script below

```
./uninstall-talkcalendar
```

You can open the BASH script installer using a Text Editor to view the code. Talk Calendar is installed into the directory "/usr/bin/talkcalendar". One advantage of using a BASH script installer is that the code can be inspected to show exactly what is occurring. 

## Calendar Interface

Talk Calendar uses a month view calendar with a bottom panel to display day events when a day is selected. To create a new event select a day on the calendar and either select the "new event" menu item or press Ctrl+N. To edit an event, select it in day view panel and then either select the "edit event" menu item or press Ctrl+E. Likewise to delete an event select it in the day view panel and use the "delete event" menu item or press the delete key. 

Use the File->Export menu item to export a calendar as an iCalendar file for backup purposes. These typically use the file extension ".ical" or ".ics". The [iCalendar standard](https://icalendar.org/) is an open standard for exchanging calendar and scheduling information between users and computers.  An icalendar file is a plain text file and so can be viewed and modified using a standard text editor. 

Pressing F1 invokes the information window which can also be selected from the menu using the Help->Information menu item. The information window shows the keyboard shortcuts, how many records are in the calendar database, the Sqlite version being used on the system, the desktop font and scale factor and the status of the speech synthesizer. The About dialog displays the Talk Calendar version number.

### New Event
![](talkcalendar-new-event.png)

### Calendar Tooltips
![](talkcalendar-tooltip.png)

### Preferences
![](talkcalendar-preferences.png)

You can change the today and event colours by clicking on the colour buttons and using the colour picker.

![](colour-picker.png)

### Information (F1)
![](talkcalendar-info.png)

The keyboard shortcuts for creating, editing and deleting events are shown below.

```
CONTROL+N = new event
CONTROL+E = edit selected event
DELETE = delete selected event
```


## Dark Theme

You can select a dark colour scheme from the preferences dialog. This uses a dark background with white text on the user interface elements. You can change the today and event colours to suit the dark theme.

![](talkcalendar-dark-theme.png)

## Talking

* Make sure the "Enable Talking" check button in the preferences window is ticked and the Flite speech synthesizer is installed (see the speech synthesis section below)

* Press the ***T key*** to readout the current time (talking clock)

* Click on a calendar day to read out the date and any event details

* The space bar can also be used to read out events on a selected day

## Font, Colour, Icons

### Font

Apparently you should now use ***system settings*** rather that in-app settings with GNOME based desktops and GTK4 applications.

Consequently, font, font size and text scaling are no longer changed from within Talk Calendar but done at the ***system level***. One way to do this with the GNOME desktop and the Ubuntu Desktop is to use the GNOME Tweaks tool which is installed as shown below.
 
```
sudo apt install gnome-tweaks
```

![](gnome-tweaks.png)

GNOME Tweaks can also be used to add Talk Calendar to the startup applications. Talk Calendar can then read out the date and any day events when the computer is switched on.

Xfce uses its own "Appearance" settings window which allows the default font to be changed and so you don't need to install Tweaks.

### Colour

The today and event calendar colours are set using the colour buttons in the preferences dialog. 

## Speech Synthesis

The Flite speech synthesizer is used as the speech engine and this has to be installed separately. With Debian and Ubuntu based distributions this is done using the command below.

```
sudo apt install flite
```

### Building on Ubuntu 24.04 and Debian 13 (x86 Hardware)

To build Talk Calendar from source you need the gcc compiler, GTK4, GLIB, and SQLITE development libraries. You need to install the following packages.

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


## Compile Notes

The Talk Calendar 0.4 series is being developed using both Debian 13 Trixie and Ubuntu 24.04. Debian 13 uses GTK 4.18 while Ubuntu 24.04 uses GTK 4.14. The Talk Calendar 0.3 series was developed using Debian 12 which uses GTK 4.8.

A model view design has been used based around a CalendarEvent type which is subclass of GObject. This allows the use of GListStore which is an array-like list implementation. A GListStore is a concrete implementation of the GListModel interface. GListView is used to display data from the model.

With GTK 4.12 onwards the GtkFileDialog API is no longer signal based but callback based using an asynchronous pattern. This allows an asynchronous, non-blocking function to be structured in a way similar to an ordinary synchronous function. File dialog windows to export and import ical files (for backup purposes) have been implemented using this approach and this code is not compatible with GTK 4.8 (Debian 12). 

GTask allows a task to be called inside a thread and is now used to play audio rather than the previous approach which used GThread and GMutex. With GTK4 it appears that the preferred way to perform work in a thread is to use GTask. The code now uses [g_task_run_in_thread()](https://docs.gtk.org/gio/method.Task.run_in_thread.html) so that audio is played in a separate background thread. The function g_task_run_in_thread() turns a synchronous operation into an asynchronous one, by running it in a thread. Apparently, GTask maintains a thread pool that is based on the number of CPUs available (i.e. supports multiple CPU-cores). 

Talk Calendar uses a GTK4 custom calendar which allows both visual markers and tooltips to be applied. A dark theme can be used with the today and event colours changed using the colour buttons in the preferences dialog.

The latest version  of Talk Calendar (0.4 series) can be used with Ubuntu 24.04, Debian 13 (but not Debian 12 for the reasons discussed above) and Fedora 41 and above.

## GTK4 vs libadwaita

With the latest GNOME changes it appears that only applications built with libadwaita (the default Adwaita theme for GNOME based desktops) respect system-wide accent colours. The libadwaita library is built on top of GTK4 and provides widgets that adhere to the [GNOME Human Interface Guidelines HIG](https://developer.gnome.org/hig/). It is used by GNOME developers to ensure that applications look and behave consistently within the GNOME desktop environment. The separation between GTK (the core toolkit) and libadwaita (the GNOME design language implementation) appears to be a deliberate strategy to allow other desktop environments (Xfce, Cinnamon, MATE) to develop and use GTK4 applications.

Talk Calendar is a GTK4 application and is not a libadwaita application. The means that it is not GNOME HIG compliant and so accent colours are not supported when using Debian 13 Trixie GNOME. I have developed a small libadwaita Calendar demo as shown in the screenshot below to demonstrate the use of accent colours on Debian 13 GNOME. 

![](debian13-accent-colour.png)

However, the application would not run on a default [Xfce4 Wayland](https://github.com/crispinprojects/xfce4-wayland) desktop without installing libadwaita and supporting libraries. Depending on your system setup this can be done using the commands below but other libraries may be needed. 

```
sudo apt update
sudo apt install libadwaita-1-0
```

Even when I got the libadwaita calendar demo to run on Debian 13 Xfce only the Debian default system colours (dark blue/light blue) were displayed as there is no accent colours dialog. 

Debian 13 Trixie (and Ubuntu) based distros have the GTK4 runtime installed by default. This means that Talk Calendar just runs without installing libadwaita.

Talk Calendar has not been rewritten as a libadwaita application using the GNOME HIG philosophy. Although a Talk Calendar libadwaita application would run on the GNOME desktop it would not run on other GTK desktops such as Xfce with out installing supporting libraries. Xfce and other GTK desktops have not officially adopted the GNOME HIG philosophy as they maintain their own system dialogs (e.g. Appearance dialog) and ecosystem. 

The GNOME HIG discourages the [use of preferences](https://wiki.gnome.org/Design(2f)HIG(2f)Planning(2f)Configuration.html) saying "using preferences as a band-aid is the root of much UI evil" and then "As far as possible, applications should be designed in order to not require manual configuration". Talk Calendar does allow users to change colour and theme preferences and choose other display options and so it is not GNOME HIG compliant in this respect. Sorry about that.

Talk Calendar supports a dark theme which can be selected using the preferences dialog. The today and event day colours to be changed to suit the dark colour scheme using the colour picker so that the user can select their own [accent colours](https://www.bbc.co.uk/homes/design/colour_wheel.shtml). The dark theme worked on an [Xfce Wayland desktop](https://github.com/crispinprojects/xfce4-wayland).

It appears that GTK5 will continue to be a general-purpose toolkit but likely to be Wayland only with web technologies used for styling. Assuming GTK5 remains a general toolkit other desktop environments such as Xfce, Cinnamon, MATE etc. will be able to use it to develop Wayland applications and apply their own themes and design. However, as GNOME drives changes in GTK that align with its GNOME HIG philosophy, the more difficult it may become for other desktop environments to use GTK applications without adopting libadwaita. 

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

To check the installed version of the GTK4 development libraries use the command below.

```
dnf list gtk4-devel
```

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

* [GNOME Builder](https://builder.readthedocs.io/index.html) is a free and open-source Integrated Development Environment (IDE) which can be used for developing GTK4 and GNOME applications.

* [Sqlite](https://www.sqlite.org/index.html) is open source and in the [public domain](https://www.sqlite.org/copyright.html).

* [Flite](https://github.com/festvox/flite)

* [Debian](https://www.debian.org/)

* [Fedora](https://fedoraproject.org/)

* [Ubuntu](https://ubuntu.com/download/desktop)
