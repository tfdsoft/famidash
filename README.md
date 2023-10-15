# famidash

Geometry Dash but on the Famicom/NES.  
The end goal is to demake the initial release of the original game (Update 1.0)  

## TODO

do this stuff (ordered from most important to least important):  
- [ ] ship  
- [ ] gravity  
- [ ] level ending  
- [ ] title screen  

# Building
## Ubuntu/Debian:  
Clone the repo: ``git clone https://github.com/zephyrside/famidash.git``  
Install cc65: ``sudo apt-get install cc65``  
Run ``make`` to build the ROM, ``make clean`` to clean.    

## Windows:  
Download the repo ZIP and extract it to somewhere.  
Run ``build.bat`` to build the ROM, ``clean.bat`` to clean.  

## MS-DOS:  
[Install DOSBOX-X.](https://dosbox-x.com/)  
Locate the ``.conf`` file, and scroll down to the ``autoexec`` section.  
add lines to mount and go to your C drive:  
``path\to\directory`` is the path on your PC where the virtual C drive will be. Example: ``C:\DOS``
```
mount C: path\to\directory 
C:
```

Install DJGPP. ZIPs for the current release can be found [here.](https://www.delorie.com/pub/djgpp/current/v2gnu/)  
Download these ZIP files:  
```
bnu2351b.zip - Assembler/Linker
csdpmi7b.zip - CWSDPMI DOS extender
djdev205.zip - Basic runtime/dev package
fil41br3.zip - GNU fileutils
mak43br2.zip - GNU Make
txt20br3.zip - GNU textutils
```

Create a directory named ``djgpp`` in the directory you mounted as the virtual C drive in DOSBOX and extract the contents of each zip into this directory.  
Add these lines to the start of autoexec:  
```
set PATH=C:\DJGPP\BIN;%PATH%
set DJGPP=C:\DJGPP\DJGPP.ENV
set OS=MSDOS
```  

Download the repo ZIP and extract it to somewhere. in the virtual C drive.  
Run DOSBOX-X, run ``make`` to build the ROM, ``make clean`` to clean.  