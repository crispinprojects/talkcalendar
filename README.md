# Talk Calendar

Talk Calendar is a personal desktop calendar for Linux which has some speech capability for reading out dates, event summary words and event times.

Talk Calendar has been developed using C++ and Qt 6.

A screenshot of Talk Calendar is shown below. 

![](talkcalendar.png)

## Core Features

* built with Qt 6
* month-view calendar
* export and import iCalendar files (backup and restore)
* calendar tools such as calculate Easter and search for events
* built-in speech synthesizer
* Sqlite3 database used to store events

## Pre-built binary

A pre-built binary of the latest version of Talk Calendar for x86 Linux computers is available and can be downloaded from the binary directory. This has been tested using Debian Trixie KDE.  Once downloaded and unzipped make sure that Talk Calendar has executable permissions before running. To change permissions and run Talk Calendar from the terminal use the commands below.
```
chmod +x talkcalendar
./talkcalendar
```


## Desktop File

To install Talk Calendar locally copy the  "talkcalendar.desktop" file into in the ***~/.local/share/applications/***  directory. If the applications directory does not exist create it. You will need to modify the desktop file so that it uses your user name and the directory where you install local programs. 

A desktop file has a .desktop extension and provides metadata about an application such as its name, icon, command to execute and other properties. The "talkcalendar.desktop" file is shown below. You need to modify this by using your own user name and directory locations. In this example it is assumed that local applications are installed in a folder called Software (/home/your_user_name/Software). Some people use a folder called "Programs". The Exec variable defines the command to execute when launching an application, in this case, the "talkcalendar" binary executable. The Icon variable specifies the path to the icon file associated with the application. The Path variable specifies that Talk Calendar should use this directory as its working directory and so is where the calendar database is stored. In a .desktop file, you need to use absolute and full paths.

```
[Desktop Entry]
Version=0.6.2
Type=Application
Name=Talk Calendar
Comment=Talking calendar
Icon=/home/your_user_name/Software/talkcalendar/calendar.png
Exec=/home/your_user_name/Software/talkcalendar/talkcalendar
Path=/home/your_user_name/Software/talkcalendar
X-GNOME-UsesNotifications=true
Categories=Office;
MimeType=text/calendar;
StartupNotify=true
Name[en_GB]=TalkCalendar
```

Copy your modified  "talkcalendar.desktop" file to ***~/.local/share/applications/***. To do this you can use your graphical file manager or the terminal command below.

```
cp talkcalendar.desktop /home/your_user_name/.local/share/applications
```

Again change "your_user_name" to your user name. Note that ***.local*** is a hidden directory and you need to tick the "Show Hidden Files" option in the file explorer to display it.

You can now run Talk Calendar Calendar from the system menu. It should be located in the "Office Category". 

You can also copy your modified  "talkcalendar.desktop" to ~/.config/autostart so that Talk Calendar starts up when the computer is switched on.

## Calendar Interface

Talk Calendar uses a month view calendar with a bottom list view to display day events when a day is selected. To create a new event select a day on the calendar and then the "new event"button. To edit an event, select it in day list view and then select the "edit event" button. Likewise to delete an event select it in the day list view panel and use the "delete event" button. 

Use the File->Export menu item to export a calendar as an iCalendar file for backup purposes. These typically use the file extension ".ical" or ".ics". The [iCalendar standard](https://icalendar.org/) is an open standard for exchanging calendar and scheduling information between users and computers.  An icalendar file is a plain text file and so can be viewed and modified using a standard text editor. 

If talk is enabled select as day on the calendar to read out the day events. Press the spacebar to speak events again for the selected day. Press the T-key to speak the current time.

### New Event
![](talkcalendar-new-event.png)
![](talkcalendar-with-event.png)

### Preferences
![](talkcalendar-preferences.png)

### Search
![](talkcalendar-search.png)

Executing a search populates the main list view with the results. Just click on another calendar date to clear.

### Easter Calculator
![](talkcalendar-easter.png)

### Information
![](talkcalendar-info.png)


### Events Database

Events are stored in an [Sqlite](https://www.sqlite.org/index.html) database. SQLite is a small, fast and full-featured SQL database engine written in C. 

### Export and Import iCalendar Files

Talk Calendar allows a personal calendar to be exported as an iCalendar file. These typically use the file extension ".ical" or ".ics". The [iCalendar standard](https://icalendar.org/) is an open standard for exchanging calendar and scheduling information between users and computers.  An icalendar file is a plain text file and so can be modified using a standard text editor. 

You should backup your events by using the File->Export iCal menu item. If you then corrupt your database, you can clear all events and then use the File->Import iCal to restore exported events. 

### Recurring Events

The only recurring event type that is currently supported by Talk Calendar is yearly. This is required for events such as birthdays and anniversaries. The parser uses icalendar [RRULE](https://icalendar.org/iCalendar-RFC-5545/3-8-5-3-recurrence-rule.html) to determine if an event is yearly (e.g. birthday).

## Updating

To update from the Talk Calendar 0.5 series to the 0.6 series export the current calendar to an ical file and then import it into the new version of Talk Calendar. The Talk Calendar 0.6 series uses Qt 6.


## Speech Synthesizer 

Talk calendar has a built-in concatenative diphone speech synthesizer which uses an Overlap-Add (OLA) vocoder. This has been coded from scratch to read out the date, time and event summary words. This is work in progress and will be updated to add new features and functionality. You can find out more on how I developed the Talk Calendar speech synthesizer [here](https://github.com/crispinprojects/diphone-talker). The vocoder is the component responsible for taking "information" (the diphones) and generating the final audio samples.

Because my diphone speech synthesizer is experimental and work-in-progress you can use espeak instead by selecting the option in the preferences dialog. This requires that espeak-ng is installed separately as Talk Calendar simply acts a speech dispatcher when the espeak preference is selected. On Debian/Ubuntu, run 

```
sudo apt install espeak-ng.
```
On Fedora, run 
```
sudo dnf install espeak-ng.
```

## Note for GNOME Users

To scale Talk Calendar to match the GNOME theme write a run application BASH script as shown below.

```
#!/bin/bash
QT_SCALE_FACTOR=1.5  /path/to/software/talkcalendar
```

QT_SCALE_FACTOR is an environment variable used to adjust the size of user interface elements based on the display's pixel density. QT_SCALE_FACTOR values greater than one increases the size of UI elements. For example, a QT_SCALE_FACTOR of 2.0 will double the size of components.

With Debian you can install the adwaita-qt6 theme engine and Qt runtime libraries as shown below.
```
sudo apt install adwaita-qt6
sudo apt install qt6-base-dev 
```

### Source Code 

The source code is found in the src directory. It is being developed and tested using Debian 13 Trixie KDE.

## Dependencies

Talk Calendar requires the following system dependencies to run and speak:

* **Qt 6.5+** (Core, Gui, Widgets, Sql)
* **SQLite 3** (Database storage)

### Installation on Debian 13 / Ubuntu 24.04 (x86 Hardware)

To build Talk Calendar from source you need install the following packages. You need to install C++ (build essential), Qt 6 development library/ tools and CMake integration package for Debian.

```
sudo apt update
sudo apt install build-essential cmake ninja-build
sudo apt install qt6-base-dev qt6-base-dev-tools
```

## Compile the Project

    1. Launch Qt Creator.
    2. Open Talk Calendar Project ( File > Open Project).
    3. Make sure the build system is CMake (this is the modern standard).
    4. Kits: make sure "Desktop Qt 6.x.x" kit is selected
    5. Build and run
    
    
### Building on Fedora

With Fedora you need to install the following packages to compile Talk Calendar.

```
sudo dnf groupinstall "Development Tools" "C Development Tools and Libraries"
sudo dnf install cmake gcc-cpp
sudo dnf install qt6-qtbase-devel qt6-qt5compat-devel qt6-qtbase-sqlite
```

## Versioning

[SemVer](http://semver.org/) is used for versioning. The version number has the form 0.0.0 representing major, minor and bug fix changes.

## Author

* **Alan Crispin** [Github](https://github.com/crispinprojects)

## Project Status

Active and under development.

## Acknowledgements

* [Debian](https://www.debian.org/)

