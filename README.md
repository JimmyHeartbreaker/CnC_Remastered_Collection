# CnC_Remastered_Collection

This fork is a debugging tool to replay C&C scenarios through a console app. This can be a lot handier than launching the whole game etc etc.

So far only tested with Tiberian Dawn campaign.

### How to use:

- Take the TiberianDawn.dll and drop it into your mod data folder.
- Run the mission as far as you need then exit. Inside the CNC root folder (e.g. \steamapps\common\CnCRemastered) there should be an events_in.txt.
- Take this file and drop it into the CAndCDebugger source directory (replacing the existing one). That file should get copied to the output directory when building (seams a bit flaky with C++ projects, maybe someone could enlighten me as to a better way).
- Debug and all the dllInterface functions that are stored in the file should be execute exactly as they were originally. The game should run quickly to the end and exit.
