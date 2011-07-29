# The TDM project

## The Name

`tdm` means "Todos Devem Morrer", or "All Must Die" in english. This name
is motivated by the actual stage of the game where you're supposed to do
nothing except protect yourself and shoot every spaceship in the screen.

## History/Development

The project arised as an experiment outside of the main subject of
Mathematics students to relax and do something funny at the end of the
day (we were allowed to work on this only after 6:00pm).

This software is written in C+++ and we make use of libraries like
[irrLich][0] and free part of [irrKlang 3D][1] and sound engines
respectively to provide a reasonably beautiful experience in playing the
game. The models for spaceships and ambient rooms were done using
[Blender][2].

## Purpose

The purpose of this project is to provide moments of fun to people
involved in developing it and hopefully to players. We hope to have at
least one that is not a developer...

## Features

These are some of the features we would like to have in this game:

* 3D graphics (altought only bi-dimensional movements are allowed)

* Easy gameplay 

* Joystick/Keyboard support.

* Local/Network Multiplayer 

* Select ships, levels and missions 

A few of them are already supported.

## Instructions for compilation

To compile `tdm` using the provided Makefile you must have in the parent directory both [IrrLicht][0] (version 1.5.2) and [irrKlang][1] (version 1.3.0) trees unzipped and compiled. [IrrKlang][1] comes compiled by default and is ready for use, but [irrLicht][0] doesn't. To have it ready for use you should have `libglu1-mesa-dev` and `libxxf86vm-dev` installed on your system. Once this is done just type `make` on `tdm` project directory to get it compiled and then type ./tdm to run the game, selecting the video driver to be used.

## Licensing

This software comes licensed under [GNU GPL version 3][3].

[0]: http://irrlicht.sourceforge.net/
[1]: http://www.ambiera.com/irrklang/
[2]: http://www.blender.org/
[3]: http://www.gnu.org/licenses/gpl.html
