# Talk Calendar

Talk Calendar GTK4 Diphone is a talking desktop calendar for Linux. It uses a built-in diphone speech synthesizer. It has been developed using C and [GTK4](https://docs.gtk.org/gtk4/).

![](talkcalendar.png)

## Installer

A 64 bit prebuilt binary and bash script installer is available and has been released.

Download and extract the release file (talkcalendar-release-055.tar.xz) and then run the bash script installer from the terminal as shown below and follow the install instructions.

```
./install-talkcalendar.sh
```

The installer must have executable permissions. The installer assumes that you are a member of the sudo group. It also assumes that the GTK4 and the ALSA libraries are installed. These are installed by default in Debian and Ubuntu GTK distros. Please see the release notes for more information. It also explains how to fix any of these issues. The installer has been tested with Linux distributions that have GTK4 in their repositories such as Debian 12 and Ubuntu.

There is also an uninstall bash script

Talk Calendar uses an Sqlite3 database for storing events and the installer will place this in your home directory. Sqlite is normally installed by default. With Debian (Ubuntu) based distributions you can check the version of Sqlite installed on your system using the terminal command below.

```
apt policy sqlite3
```



### Installer Troubleshooting

In most cases the installer will just run as the required libraries will be installed by default and the user will be a member of the sudo group.

* Not a member of the sudo group

The installer assumes that you are a member of the sudo group. If you have installed Debian 12 with a root password then you will have to add yourself to the sudo group. The commands below show how to do this.

```
su -
adduser your-user-name sudo
```

Then restart.

* No GTK4 library

The installer assumes that the GTK4 library are installed. These are installed by default on Debian and Ubuntu GTK based distros but sometimes are not installed on some spins or if creating a desktop from a Debian base install. To install it use the command below.

```
sudo apt install libgtk-4-1
```

* No ALSA library

The installer assumes that the [Advanced Linux Sound Architecture](https://www.alsa-project.org/wiki/Main_Page) (ALSA) library is installed. This provides audio and MIDI functionality to the Linux operating system and is installed by default in Debian and Ubuntu distros. However if building a desktop from a Debian base install you will need to install ALSA as shown below.
```
sudo apt install alsa-utils
```

## Core Features

* built with C and GTK 4.8.3 (Debian 12)
* bespoke custom calendar which allows dates with events to be marked up
* event summary, location, start and end time can be entered and edited
* priority and is-yearly can be used
* Sqlite3 database used to store events
* built-in diphone speech synthesizer
* alpha binary release with bash script installer for 64-bit GTK4 distributions using GTK4 


## Calendar Usage

### Adding New Event

* Select event date using the calendar
* Click the New button on the header bar to invoke the "New Event" window
* Enter the event summary (e.g. birthday, anniversary, doctor, dentist etc.)
* Enter the description (optional)
* Enter the location (optional)
* Enter start and end times (or all day)
* Events are sorted by start time when displayed
* Navigate through the year using the calendar to add events

![](talkcalendar-new-event.png)

When a creating a new event you can check "Send Notification" which will send a system notification when Talk Calendar is started on the day in which the event occurs.

### Editing Existing Event

* Select the event in the list view and click the Edit button on the header bar to edit
* Change details as appropriate


### Preferences

* Use the Preferences window in the hamburger menu to change  options

![](talkcalendar-preferences.png)

You can use 12 hour format and event end-times can be shown in the list view. If public holidays is selected then the date label shows the public holiday (UK only) which is also spoken.

Talk options can be changed.

## Talking

* Press spacebar to speak the date and event summary.

### Information

```
menu->Information
```

The Information dialog to shows the keyboard shoutcuts, how many records are in the database, the Sqlite version being used on the system, the desktop font and scale factor.

![](talkcalendar-information.png)


* Use the About dialog to display current version.

### Keyboard Shortcuts

```
Speak           Spacebar
Today           Home Key
```

## Startup Applications

Add Talk Calendar to your start-up programs to read out the date and any event details when the computer is switched on.

With GNOME based desktops use the GNOME "Tweak Tool" to add Talk Calendar to your startup applications if required.

## How is Speech Generated?

Words are formed as sequences of elementary speech units. A phoneme is the smallest unit of sound that distinguishes one word from another word and there are 44 phonemes in the English language. A diphone is a sound unit composed of two adjacent partial phonemes i.e. the second half of the first phoneme and the first half of the second phoneme. The synthesizer uses a set of pre-recorded diphone sound samples and concatenates diphone wav files to produce speech output for a given text input.

The folder containing the diphone wav files should be placed into the application binary (executable) working directory. The diphone collection was created by Alan W Black and Kevin Lenzo and more information can be found using the links in the Acknowledgements. The diphone license can be found [here](https://github.com/hypnaceae/DiphoneSynth/blob/master/diphones_license.txt).

The diphone speech synthesizer uses a small dictionary of approximately 56,600 English words. If a word is not recognised by the dictionary it is skipped over. More words will be added in future updates.

### Events Database

Events are stored in an [Sqlite](https://www.sqlite.org/index.html) database. SQLite is a small, fast and full-featured SQL database engine written in C. 

### Backup Restore Events Database

A first attempt of a backup and restore system has been implemented in case the Sqlite events database becomes corrupted (e.g. by using another external program to open it or by attempting to vacuum it). You should backup your events by using the export to CSV file menu item which will create an events.csv file in the working directory (keep this safe and make another copy if necessary). If you then corrupt your database, you can clear all events from the Sqlite database and then use the import from  CSV restore option. If you completely corrupt your Sqlite database called calendar.db then rename it and restart Talk Calendar which will create a new empty database and restore into this. 

I have not tested what will happen if you attempt to vacuum your database externally and then restart Talk Calendar with this.

## Build From Source

The C source code for the Talk Calendar project is provided in the src directory.

[Geany](https://www.geany.org/) can be used as a source code editor for opening, viewing and then compiling the Talk Calendar C code. Geany is lightweight and has an integrated terminal for building the application.

You need the GTK4 development libraries and the gcc compiler. The code has been compiled using GTK 4.6.9 amd64 (Ubuntu 22.04). To determine which version of GTK4 is running on a Linux system use the following terminal command.

```
dpkg -l | grep libgtk*
```

To build Talk Calendar you also need the Sqlite3 development libraries. With Debian and Ubuntu you install these using the commands below.

```
sudo apt install sqlite3
sudo apt install libsqlite3-dev
```

To check the installed version use the command below.

```
sqlite3 --version
```

### Building on Ubuntu and Debian Bookworm

With both  Debian Bookworm and Ubuntu and you need to install the following packages to compile Talk Calendar.

```
apt install build-essential
apt install libgtk-4-dev
apt install libasound2-dev
```

The packages:

```
apt install libglib2.0-dev
apt install alsa-utils
```

are needed but should be installed by default.

With Ubuntu 22.04 the base GTK4 libraries are installed by default. With other Ubuntu based distributions (spins) you may have to install these using the command below.

```
sudo apt install libgtk-4-1
```

Use the MAKEFILE to compile.

```
make
./talkcalendar
```

Audio requires that the diphone directory containing the diphone wav files be located in the working directory. Example diphones are included  but you can create you own.

### Building on Fedora

With Fedora you need to install the following packages to compile Talk Calendar.

```
sudo dnf install gtk4-devel
sudo dnf install gtk4-devel-docs
sudo dnf install glib-devel
sudo dnf install alsa-lib-devel
```
### Roadmap

* ~~backend sqlite database~~ (done)
* ~~backup and restore database (export/import csv file)~~ (done)
* ~~public holiday calendar marks~~
* ~~startup notifications~~ (done but see note below)
* ~~check and read out upcoming events~~ (basic code structure completed)
* ~~test building talkcalendar with GTK 4.12~~ (see note below)
* ~~deployment release with Git tag~~ 
* ~~bash script installer~~ 
* remove GTK4 classes being depreciated (ongoing - see below)
* expand speech dictionary (ongoing)
* refactor preferences dialog code
* refactor startup code (checks)
* refactor custom calendar code 
* calendar styling (see note below -***stalled***)
* calendar styling: event colour user choice (see note below)
* calendar styling: public holiday calendar colour
* multi-day events 
* read time
* GTK desktop testing (ongoing see below)
* bug testing (ongoing)
* more releases
* explore packaging options (produce a reference example)

## Testing 

### GTK4 Deprecating Classes

GTK have announced that they are [deprecating a number of GTK4 classes](https://blog.gtk.org/2022/10/30/on-deprecations/) as an early outlook at changes that will appear in the next major release that will break API compatibility. The full list of depreciated classes can be found in the list of [GTK4 api classes](https://docs.gtk.org/gtk4/#classes) and generally listed as GTK4.10 or GTK4.12 depreciations. Most current Linux distributions are using GTK4.8. Talk Calendar had been using a number of these classes and so recent work has involved going through the source code line-by-line removing class functions that will be depreciated. 

I have tested building Talk Calendar with ***GTK4.12*** (Ubuntu 23.10). It builds. However, if you take a binary built with GTK4.12 and try to run it on Debian 12 which uses GTK4.8 it fails to run. You need to use a binary built on Debian 12 on Debian 12 and a binary built on Ubuntu 23.10 on Ubuntu 23.10. However, a binary built on Debian 12 with GTK4.8 runs on Ubuntu 23.10. It appears from my testing that a GTK4 app built on a lower version will run on a higher version but the reverse is not true. 

The main reason why I am not currently using a file dialog for saving a backup file is because the functions [gtk_file_chooser_dialog_new](https://docs.gtk.org/gtk4/ctor.FileChooserDialog.new.html) and [gtk_dialog_new_with_buttons](https://docs.gtk.org/gtk4/ctor.Dialog.new_with_buttons.html) are being depreciated in GTK4.10. I believe that you will have to use [GtkFileDialog](https://docs.gtk.org/gtk4/class.FileDialog.html) instead.

GTK developers are planning the [GTK5](https://www.phoronix.com/news/GTK5-Likely-After-GTK-4.12) toolkit discussing making it a Wayland only [release](https://www.phoronix.com/news/GTK5-Might-Drop-X11).

### Calendar Style

Currently, Talk Calendar uses Pango attributes and markup for adding some style and colour to the calendar. Pango is the text layout system used by GDK and GTK.

The platform library [libadwaita](https://gnome.pages.gitlab.gnome.org/libadwaita/doc/main/style-classes.html) used by GNOME desktops uses style classes such as “title-1”, "title-2", and “dim-label” etc. which can be used by GTK4 applications with the gtk_widget_add_css_class() function. An example is shown below.

```
gtk_widget_add_css_class (label, "title-2");
```

As I understand it, GTK4 does not define style classes and this is left to the platform library (libadwaita). GTK4 gives you "labels", "buttons" and other GUI components while libadwaita is used to style these following GNOME's Human Interface Guidelines (HIG). 

I need to do more research into GTK4 styling with a platform library. Consequently, I have placed styling lower down in the road map list as I need to learn how to do this and decide if it is a good idea to lock in the application to a platform library or not. There is a Github discussion on this topic entitled ["Please don't use LibAdwaita library"](https://github.com/xournalpp/xournalpp/discussions/5301).

The [gtk_css_provider_load_from_data()](https://docs.gtk.org/gtk4/method.CssProvider.load_from_data.html) function which I used previously in the GTK3 version of the application is being depreciated and so all code using it has been [removed](https://gitlab.gnome.org/GNOME/gtk/-/commit/f2a297f56d7b0f749ae8b5ef5b853951ff30a89d). I believe gtk_css_provider_load_from_string() could be used instead in GTK 4.12. However, I am using GTK 4.8.3 for developing this application which is found in the Debian 12 package repositories. It appears that you can still use an application-specific styling css file (e.g. styles.css) but although I developed some test code I have not gone down this route in case this approach is depreciated further down the line.

I need to add a feature to allow the user to choose the event and today colours.

Hopefully this all makes some sense to anyone reading this. In summary styling is stalled until I get a better understanding on how best to move forward. I am also monitoring how the Xfce and Budgie desktops move to Wayland as this will help.

### Wayland and X11 Distros (GNOME, Xfce, Budgie)

GTK4 supports [Wayland](https://wayland.freedesktop.org/) which is a replacement for the X11 window system protocol. The XDG_SESSION_TYPE variable stores the type of display server the system is using. To check if you are running Wayland or X11 echo the XDG (Cross Desktop Group) session type as shown below.

```
echo $XDG_SESSION_TYPE
```
It will output either "wayland" or "x11".

The GNOME desktop (i.e. GNOME Shell written in C and GTK) uses the Mutter compositor which supports both Xorg and Wayland and defaults to Wayland when the environment variable is set as shown below.

```
export GDK_BACKEND=wayland
```

To use the X11 back-end you would use.

```
export GDK_BACKEND=x11
```

Talk Calendar runs on both Debian GNOME and Ubuntu GNOME. Both use Mutter and Wayland by default. In these specific use cases Intel® HD Graphics 530 and Intel® HD Graphics 630 integrated graphics units have been used.

I have also tested Talk Calendar on Debian Xfce and Debian Budgie desktops which currently use X11 by default.

Regarding Xfce, I believe they plan to move to using a Wayland compositor and progress can be found in their [roadmap](https://wiki.xfce.org/releng/wayland_roadmap). They are working on a library called [libxfce4windowing](https://gitlab.xfce.org/xfce/libxfce4windowing) which they describe as a windowing concept abstraction library for X11 and Wayland. 

Regarding the [Budgie Desktop](https://github.com/BuddiesOfBudgie/budgie-desktop), running the apt policy command below 
```
apt policy budgie-desktop
```
shows that Debian Bookworm is using the Budgie desktop version 10.7.1-1. Using
```
inxi -Gxx | grep compositor
```
reveals that the compositor is "budgie-wm". The XDG (Cross Desktop Group) session type is X11. 

There is information on the Buddies of Budgie [Wayland blog](https://buddiesofbudgie.org/blog/wayland) about moving to a Wayland only version of Budgie using a Wayland compositor called Magpie V1.0 which was originally forked from Mutter.

A screenshot of Talk Calendar running on Budgie 10 (GTK, X11) is shown below.

![](budgie10-x11-gtk.png)

In summary testing shows that the GTK 4.8 version of Talk Calendar runs on both X11 and Wayland desktops without any known issues. With this Talk Calendar version there is no css styling. It is just raw GTK4 code (see above).

### Notifications

Startup day event notifications have now been implemented using [libnotify](https://gitlab.gnome.org/GNOME/libnotify). This library is an implementation of the [Desktop Notifications Specification](https://specifications.freedesktop.org/notification-spec/notification-spec-latest.html) which provides support for GTK and Qt applications and is ***desktop independent***. 

I have developed a small GTK4 notification tester app which can be found [here](https://github.com/crispinprojects/notification-tester) with screenshots and notes for Debian GNOME (Wayland) and Debian Budgie (X11) testing. I found that GNotification code works on Debian Budgie (X11) but not on Debian GNOME (Wayland). Consequently, I am currently using libnotify for implementing notifications in Talk Calendar.

## Versioning

[SemVer](http://semver.org/) is used for versioning. The version number has the form 0.0.0 representing major, minor and bug fix changes.

Please note that this version of Talk Calendar (Talk Calendar GTK4 Diphone) supercedes my previous and older Talk Calendar programs which have been forked. The code base has been completely re-written and so is not compatible with earlier versions. The new Talk Calendar application uses an Sqlite3 database for storing events rather than a csv file and is maintained with bug fixes while other projects are not.

## Author

* **Alan Crispin** [Github](https://github.com/crispinprojects)

## License

Talk Calendar GTK4 Diphone is licensed under LGPL v2.1. GTK is released under the terms of the LGPL v2.1 license.

## Project Status

Active.

## Acknowledgements

* [GTK](https://www.gtk.org/)

* GTK is a free and open-source project maintained by GNOME and an active community of contributors. GTK is released under the terms of the [GNU Lesser General Public License version 2.1](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html).

* [GTK4 API](https://docs.gtk.org/gtk4/index.html)

* [GObject API](https://docs.gtk.org/gobject/index.html)

* [Glib API](https://docs.gtk.org/glib/index.html)

* [Gio API](https://docs.gtk.org/gio/index.html)

* [Geany](https://www.geany.org/) is a lightweight source-code editor (version 2 now uses GTK3). [GPL v2 license](https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt)

* [Diphone Source and License](https://github.com/hypnaceae/DiphoneSynth/blob/master/diphones_license.txt)

* Diphone collection and synthesis Alan W. Black and Kevin Lenzo [2000](https://www.cs.cmu.edu/~awb/papers/ICSLP2000_diphone.pdf)

* [Sqlite](https://www.sqlite.org/index.html) is open source and in the [public domain](https://www.sqlite.org/copyright.html).

* [Embedding a file in an executable](https://www.linuxjournal.com/content/embedding-file-executable-aka-hello-world-version-5967) and [here](https://stackoverflow.com/questions/6785214/how-to-embed-a-file-into-an-executable-file).
