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
Version=0.6.5
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

Talk calendar has a built-in concatenative diphone speech synthesizer. This has been coded from scratch to read out the date, time and event summary words. 

The Talk Calendar speech engine uses a multi-stage Grapheme-to-Phoneme (G2P) pipeline to transform raw calendar text into audible speech.  

### The Processing Pipeline

1. Pre-processing is used to converts dates and times into spoken words (e.g. "Tuesday twenty-fourth February").
2. Lexicon Lookup: The engine first checks pre-defined diphone sequences for common calendar words, months and numbers.
3. Statistical Inference (Machine Learning): If the word is not in the lexicon, the engine uses a trained CART (Classification and Regression Tree) model. This model was trained on the 134,000-word [CMU Pronouncing Dictionary](http://www.speech.cs.cmu.edu/cgi-bin/cmudict#about) to automatically discover and apply phonetic patterns (like the "Magic E" or soft "C") to unknown words. The Decision Tree ensures that the Talk Calendar speech engine never "breaks" when it sees a word it does not know. It will always make the best statistical guess.
4. Diphone Concatenation: Phonemes are split into diphones (transitions) and stitched together from the audio database.
     
### Learned Phonetic Patterns

Instead of manually writing rules, the Talk Calendar engine uses Machine Learning to "understand" English [phonics](https://sounds-write.co.uk/what-are-phonemes-and-graphemes/). By analyzing the CMUdict dataset, the decision tree model discovered patterns such as:

* Context-Sensitive Vowels: Automatically identifying "Magic E" patterns to switch between short and long vowel sounds.
* Digraph Detection: Recognizing multi-letter clusters like th, sh, and ph as single phonetic units.
* Grapheme-to-Phoneme Mapping: Predicting the pronunciation of names and rare words based on statistical probability.

The Talk Calendar speech engine is work-in-progress and will be updated as I develop new features and functionality. You can find out more about diphone concatenation and the diphones used for this project [here](https://github.com/crispinprojects/diphone-talker). Currently, a diphone Overlap-Add (OLA) vocoder is used. The vocoder is the component responsible for taking "information" (the diphones) and generating the final audio samples. New vocabulary and unique pronunciations will be added to the Lexicon as I come across them.

## Speech Synthesis Technology Comparison

The Talk Calendar speech engine is extremely lightweight able to run on low-power hardware without a GPU. Below is a table which shows how it compares with other speech engines.

| Engine / System | Synthesis Type | Text Processing (G2P) | Architecture | Target |
| :--- | :--- | :--- | :--- | :--- |
| **Talk Calendar** | Concatenative (Diphone) | Trained Decision Trees (ML) | C++ / Qt | Embedded / Lightweight |
| **eSpeak-NG** | Formant (Klatt) | Rule-based | C | Ultra-low footprint |
| **Festival** | Unit Selection | Scheme / Lexicon | C++ / Lisp | Research / Unix |
| **Flite** | Diphone | Compiled G2P Trees | C | Mobile / IoT |
| **Piper** | Neural (VITS) | Phonemizer (ML) | C++ / Python | Modern High-Quality |

***Definitions:***

***Concatenative (Diphone):*** Splicing together transitions between sounds. 

***Formant (Klatt):*** Generating sound mathematically using a sound source and filters to mimic a human voice. 

***Unit Selection:*** Like diphone concatenation, but uses other types of speech units in addition to diphones such as whole words or phrases and so requires a massive database.

***Neural:*** Uses AI (Deep Learning) to predict the waveform.

***Phonemizer:*** modern name for a Grapheme-to-Phoneme (G2P) engine that turns "Hello" into /həˈloʊ/.


## eSpeak

Because the Talk Calendar speech synthesizer is experimental and work-in-progress you can use espeak instead by selecting the option in the preferences dialog. This requires that espeak-ng is installed separately as Talk Calendar simply acts a speech dispatcher when the espeak preference is selected. On Debian/Ubuntu, run 

```
sudo apt install espeak-ng.
```
On Fedora, run 
```
sudo dnf install espeak-ng.
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
5.  Build and run
    
    
### Building on Fedora

With Fedora you need to install the following packages to compile Talk Calendar.

```
sudo dnf groupinstall "Development Tools" "C Development Tools and Libraries"
sudo dnf install cmake gcc-cpp
sudo dnf install qt6-qtbase-devel qt6-qt5compat-devel qt6-qtbase-sqlite
```

## Gtk vs Qt

With the Talk Calendar 0.6 series I have moved away from using the Gtk 4 GUI toolkit to using Qt 6. When I moved the project from Gtk 3 to Gtk 4 I had issues with  the GtkCalendar component specifically with marking a calendar date which would have an event. I got around this by creating my own custom calendar component  which used css classes which allowed dates with events to be marked with a colour set by the user. My custom calendar uses features which are now going to be depreciated with Gtk 5. As explained in this [article](https://docs.gtk.org/gtk4/migrating-4to5.html) cell renderers are going away, local stylesheets are going away, non-standard CSS extensions are going away, color expressions are going away, chooser interfaces are going away along with many other depreciations. This would have meant another major rewrite of the Talk Calendar Gtk 4 application when moving to Gtk 5. 

There is another issue with Gtk application development. With the latest GNOME changes it appears that only applications built with libadwaita (the default Adwaita theme for GNOME based desktops) respect system-wide accent colours. The libadwaita library is built on top of GTK 4 and provides widgets that adhere to the [GNOME Human Interface Guidelines HIG](https://developer.gnome.org/hig/). It is used by GNOME developers to ensure that applications look and behave consistently within the GNOME desktop environment. What this means is that the styling of a Gtk application is now effectively outsourced to libadwaita. I have developed a small libadwaita Calendar demo as shown in the screenshot below to demonstrate the use of accent colours on Debian 13 GNOME. 

![](debian13-accent-colour.png)

The separation between GTK (the core toolkit) and libadwaita (the GNOME design language implementation) appears to be a deliberate strategy. With the release of Debian 13 Trixie GNOME I started to develop a Gtk4 Talk Calendar application using GtkCalendar. However, when I tried to run this with the KDE desktop the calendar day markings for events were not displayed. When I used my own custom calendar they were displayed indicating it may be due to libadwaita. Perhaps I needed to install some libadwaita library for Qt which I could not find but it was at this point I decided to switch to Qt 6. I also found that the libadwaita Calendar demo did not run on the Xfce desktop environment without installing libadwaita and supporting libraries which is rather pointless as Xfce uses its own theming system.

I know this is only hobby project but I have never been happy with the idea of outsourcing the way an application should look to an external library such as libawaita. However, this is the direction of travel with GNOME. Moving to Qt 6 was a difficult decision because so many of the major Linux distributions such as Debian, Ubuntu, Fedora etc. use GNOME (and by implication Gtk) by default. However, Qt applications run within GNOME as well as with KDE and other Qt based desktops.

## Versioning

[SemVer](http://semver.org/) is used for versioning. The version number has the form 0.0.0 representing major, minor and bug fix changes.

## Author

* **Alan Crispin** [Github](https://github.com/crispinprojects)

## Project Status

Active and under development.

## Web Links

* [Debian](https://www.debian.org/)

