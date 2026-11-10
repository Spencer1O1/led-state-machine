# Installation
So. We found out that when you have one git repo and lots of computers workin' on it, you have to do some stuff to get everyone on the same page.

The Bootstrap creates a bunch of files and things that fprime needs to operate. These things are system-dependent and mostly binary files, so they are in the .gitignore and won't be pushed to the repo.

In order to clone somebody else's fprime repo, you need to:
1. get the fprime submodule into git
1. create a local virtual environment to contain dependencies
1. install all of fprime's dependencies into the virtual environment

I'll talk about these in a little more detail. Technically you can create the virtual envinronment before you get the fprime submodule, but this procedure makes more sense. You do need to have steps 1 and 2 done before step 3 will work.

**Important:** All `bash` commands below assume that you are in the root directory of a previously-created F' project.


### 1. fprime submodule stuff
Still not sure what the right name for this is. Basically, you need to tell git that you're trying to work with the fprime repository that NASA wrote so your computer knows what fprime needs in order to run. You can do that with this command:

```bash
$ git submodule update --init --recursive
```
Not really sure what this does on a low level, but it creates a directory somewhere along the path called "lib" that has some important dependency info in it.

### 2. create a virtual environment
Now you gotta get yourself a place for all those dependencies to live. Creating a virtual environment for this is just like creating any other virtual environment, if you've done that before. The command you'll use is this:
```bash
python3 -m venv ./fprime-venv
```

If you aren't on Linux, you'll probably have to use `python` instead of `python3`. Note that can probably name your virtual environment whatever you want. I just called ours "fprime-venv" because that's what fprime calls the venv that it creates when you run the bootstrap.

### 3. install F' dependencies
Now that you have a house for the dependencies, you can have them "move in". You'll use the following command:
```bash
python3 -m pip install -r requirements.txt
```

This will look up everything that F' needs in a requirements file that we got from the submodule in step 1. 

These three steps were integral to us getting multiple people to be able to contribute to a single F' project.

<!-- originally part of README.md, moved for convenience and better organization -->
