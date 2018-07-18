# VBA-Blitz-Tendency
Void's Blitzarre Adventure: Blitz Tendency

VBA:BT is a series of resource blitzes culminating in a completed hack.

Read CONTRIBUTING.md for an overview on rules and regulations.

# Phases

Phases are *very* flexible but the general outline is something like this:

1) Blitz Part 1 (1 week, 10 chapters) / Resource Blitz (collect as many resources for the whole process as possible)
2) Blitz Part 2 (1 week, remainder of game)
3) Polish Blitz (1-2 weeks, make the game fun and presentable)

Feel free to do anything out of order, as long as it's with proper version control.

# Project Structure

Due to the very walk-in and contribute nature of the project, with the relative inexperience with git of the community,
there will be a structure for contributors, detailed here.

### Roles

**Admins** are members of the FireEmblemUniverse organization on GitHub.
These members may add **team members**, approve pull requests, and change repository settings.
Admins: Crazycolorz5, Camdar, Circleseverywhere, and StanH

Any known member of the community with minimal knowledge of git and a [Github account](https://github.com/join) may request to become a **team member** for the project.
**Team members** are expected to create feature branches, and incorporate changes from other contributors.
They are also expected to create pull requests once a feature branch is complete.
Basically, those with some knowledge of git just structure and commit the changes created from those who do not know git.
A list of team members will be maintained on the [forum page](http://feuniverse.us/t/voids-blitzarre-adventure-blitz-tendency/3969/2?u=crazycolorz5).

If you don't know git, don't be afraid! There is a [forum post](http://feuniverse.us/t/voids-blitzarre-adventure-blitz-tendency/3969/3?u=crazycolorz5) on the simplest aspects and you can ask for help from other team members or admins.
The required level of knowledge really won't be that high.

**Contributors** are everyone else. Anyone is able to contribute resources to any phase of the project.
There is no commitment to being a contributor.
However, for changes to be incorporated into the hack, you must coordinate with a **team member** to get a feature branch created.
I want to encourage as many contributions as possible. The more people we have help, the less work we need to do overall.

### Typical Contribution

1) You create a portrait/map/event file/etc.
2) You get in contact with a **team member** (via forums, discord, other), and give them the resource.
3) The team member creates a branch for the change, and commits it. They create a pull request when it passes necessary tests.
4) An **admin** approves the pull request and the change is in the hack.

For team members:
To test the changes, you must have the project repo set up and able to build. See the `Setup` section below.

# Setup

Please refer to `Setup.md` for instructions on setting up the project folder and building after cloning the repo.

# Technical Information

Everything will be assembled with ColorzCore and the Buildfile method.
The base system will be the FE8 skill system.
