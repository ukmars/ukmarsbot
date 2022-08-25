# UKMARSBOT Contributor Guide
## Purpose
This document provides guidance for making contributions to the UKMARSBOT project.

The UKMARSBOT project began in 2019 with the aim of developing a simple, fleible and affordable autonomous robot platform. The robot would be suitable for use in a number of popular small robot contest events including micromouse maze solving, wall following, line follower and drag race events. 

Here in 2022, we have many built units that have competed in contests or have been built for the fun and experience. There are a number of options for sensor boards available in this repository. There is also a good amount of software in two main repositories:
 
 - Software examples https://github.com/ukmars/ukmarsbot-examples
 - Full maze solving software: https://github.com/ukmars/ukmarsbot-mazerunner

Also, a number of builders have experimented with alternative processor boards.

## Issues

If you have suggestions for changes or improvements, or have identified a problem, then please use the [__Github Issues__](https://github.com/ukmars/ukmarsbot/issues) system to identify and discuss those them. The main developers will be automatically notified when a new issue is raised.

When contributing through raising an __Issue__ please include:
1. Identification of the component of the project to which the issue relates e.g. mainboard, line sensor etc.
1. Identification of the artefact(s) affected eg Requirements, BOM, Board Design...
1. A clear and brief description of the suggested improvement

## Contributions

If you want to develop software or hardware for the UKMARSBOT project, the best way is to fork this project on Github and generate pull requests so that these improvements may be incorporated into the original project.

There are a number of general purpose guides to making contributions to open source projects on github:

 - https://github.com/MarcDiethelm/contributing
 - https://akrabat.com/the-beginners-guide-to-contributing-to-a-github-project/
 - https://www.dataschool.io/how-to-contribute-on-github/

If git and github are not your thing, you can download the entire repository as a zip file, unpack it on your machine and beaver away on it there. On the main page of the repository is a green button labelled 'Code'. Click that and you will find a link for the zip file.

## Tools

Most of the work on UKMARSBOT involves designing Electronic circuits using appropriate Electronic CAD tools. The project was started using Autodesk Eagle which has a free-to-use version with some constraints. Some of the more recent work has been done using KiCad 6. This is a completely free-to-use tool that will run on any common desktop operating system and is unrestricted.

## Suggestions

There are two likely areas for development with this version of the robot:

- __Sensor boards__ These are what gives UKMARSBOT most of its flexibility and will change the main use of the robot. The designs in this repository are suggestions and, while they are a great starting point, can be improved significantly for more advanced or specialist use.
- __Processor Choices__ The Arduino Nano has a footprint that has been emulated by several alternatives. They are not always a great fit but several have been made to work well. It would be great if we could have some more powerful processors on modules that could simply plug straight in to the existing Nano socket andprovide more processing power or other facilities.

---
## Historical

The UKMARSBOT was being developed in several stages. The plan for the development of UKMARSBOT can be seen [here](UKMARSBOT-Project-Plan.pdf)

### Revision 1 of UKMARSBOT
The focus of the Revision 1 phase of the project was to get a limited number of boards manufactured and supporting materials to enable trial and testing to take place on a project in a school commencing in the Autumn term 2019.

To this end a small group of UKMARS members worked together to create initial items. Ideas and suggestions for improvements are always welcomed through raising an __Issue__. Given the timing constraints the project retained a strong focus on Revision 1 and a minimally function set of sensor boards.


Thanks for your ideas and help.
