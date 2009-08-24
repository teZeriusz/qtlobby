#!/usr/bin/python                                                                   
# -*- coding: utf-8 -*-

from threading import Thread
import threading
from subprocess import Popen, PIPE
import os                         

class CommandError(Exception):
        def __init__(self, value):
                self.value = value
        def __str__(self):        
                return repr(self.value)

builder_lock  = threading.RLock()

class QtLobbyBuilder(Thread):
        def __init__(self, targetDir, onMessage, onCompleted):
                Thread.__init__(self)              
                self.onMessage = onMessage         
                self.onCompleted = onCompleted     
                self.revision = "HEAD"             
                self.abort = False
		self.dir = targetDir
		self.config = "debug"
		print "QtLobbyBuilder instance created"

        def runCommand(self, command):
                print command         
                p = Popen(command, stdout=PIPE, stderr=PIPE, shell=True)
                (stdout, stderr) = p.communicate()
                if p.returncode != 0:                                   
                        self.onMessage("Error executing " + command + "!\n" + str(stderr))
                        raise CommandError("Command failed")                              
                return stdout                                                             

        def run(self):
		print "Building"
		pwd = os.getcwd()
       	        os.chdir(self.dir)
               	try:               
                       	rev = str(self.revision)
                        self.onMessage("Perforimg svn update...")
       	                self.runCommand("svn up -r " + rev)      
               	        rev = self.runCommand("svn up | perl -e '<> =~ /At revision (\d+)./; print $1;'")
                        self.onMessage("Building revision "+rev+"...")
       	                self.runCommand("qmake -spec win32-x-g++ CONFIG+=buildbot CONFIG+="+self.config)
			self.runCommand("touch src/MainWindow.cpp")
               	        self.runCommand("make")
                       	os.chdir(self.config)
                        self.runCommand("objcopy --only-keep-debug qtlobby.exe qtlobby.dbg")
       	                self.runCommand("strip --strip-debug --strip-unneeded qtlobby.exe")
               	        os.chdir("..")
                       	self.onMessage("Compiling installer...")
                        self.runCommand("makensis installer.nsi")
       	                self.runCommand("mv "+self.config+"/qtlobby.exe ~apache/qtlobby.oxnull.net/htdocs/qtlobby.r"+rev+".exe")
               	        self.runCommand("mv qtlobby_installer.exe ~apache/qtlobby.oxnull.net/htdocs/qtlobby.r"+rev+"_installer.exe")
                       	self.runCommand("mv "+self.config+"/qtlobby.dbg ~apache/qtlobby.oxnull.net/htdocs/qtlobby.r"+rev+"_symbols.dbg")
                        self.onCompleted({"Exe": "http://qtlobby.oxnull.net/qtlobby.r"+rev+".exe", \
       	                                  "Installer": "http://qtlobby.oxnull.net/qtlobby.r"+rev+"_installer.exe", \
               	                          "Debug symbols": "http://qtlobby.oxnull.net/qtlobby.r"+rev+"_symbols.dbg"})
                except CommandError:
       	                pass
               	finally:
                        os.chdir(pwd)

def message(msg):
        print "[MESSAGE] " + msg;

def completed(links):
        print "Completed!"
        for k in links.keys():
                print k + ": " + links[k]

if __name__ == "__main__":
        builder = QtLobbyBuilder("../qtlobby", message, completed)
	builder.revision = "HEAD"
        builder.start()

