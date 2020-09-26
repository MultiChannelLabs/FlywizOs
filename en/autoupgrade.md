# Automatic card upgrade
In the case of screen damage or inaccurate touch, if we want to upgrade the system, we can create a file in the root directory of the TF card
**zkautoupgrade** (Note: The file has no suffix)

![](images/Screenshotfrom2018-06-07195801.png)

In this way, the machine will automatically check the upgrade item after the card is inserted, and the upgrade will start after 2 seconds by default; if you need to control the time before the upgrade, we can open the `zkautoupgrade` file and fill in the corresponding number, the unit is seconds; after the upgrade is completed , The system restarts, remember to pull out the TF card to prevent automatic upgrade again.
