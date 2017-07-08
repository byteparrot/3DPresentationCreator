
## What is the 3D Presentation Creator
3D presentations is a plugin for the Unreal Engine 4 and can be used to turn a level into a presentation. The only necessary setup is to put the plugin in the Plugin folder, activate it inside the project and click on one of the new buttons to configure the level for presenting. After the initial setup, it is possible to place slides into the level and start the presentation by just pressing play*.

## How-to use the 3D Presentation Creator
## Initial Setup
Put the presentation plugin folder into the Plugin folder of the project which should be configured for presenting:

### Start Project
After starting the project you should be notified that new plugins are available. It should also be automatically enabled. If it isn’t, check the “Enabled” checkbox and restart the editor as prompted.

### User Interface
#### Toolbar Extension
After starting the editor with the plugin enabled, one can see the new buttons in the toolbar with the basic functionality to get a presentation.

#### Presentation Tools
After clicking on the Tools Button inside the PresentationTools Drop Down menu, a new tab shows up with extended functionality for the presentation creation process.

#### Slide Tools
When a slide is selected, the details panel contains all the necessary information to change the slide’s content.

### Basic Presentation Functions
#### Create a Slide
After pressing one of the “Add Slide” Buttons;
A new Slide appears right where the camera is in the Viewport.

#### Configure Presentation Mode
When using one of the functions from the Presentation Tool or pressing the “Configure Presentationmode” buton, the level is configured in “presentationMode” – which means that the GameMode in the world settings of this level is changed to the presentationMode. In many projects after this is done the presentation starts after pressing play from now on. If there is some other logic that overrides the game mode in the level initialization or in the settings, this has to be changed to be able to start the presentation. 

#### Edit Slide
The Slide Tools are located in the details panel of the engine.
When selecting a slide there are a bunch of options for this slide.

These buttons can change the index of this slide to occour sooner or later in the presentation, reset the transition curve or update the slide if the proportions haven’t been updated or the viewport shows different text than the details panel.
Slide Template can be changed to different layouts.

Title, Sections, Image, colors directly change the slide’s appearance and content.

Custom Template can be set to a custom UMG widget. The slide template above has to be set to custom to make use of this function.

Transition Duration are the seconds that the camera needs to the next slide. Auto Continue Time can be used to trigger the switch to the next slide after seconds or 0 to not make use of this feature.

Triggers can be added here – these are blueprints that implement the Trigger Interface. These blueprints are then triggered as soon as the slide is in focus.

#### Custom Slide Design
When pressing the “new custom design” button, a dialog appears that allows you to edit the name and location of the new design.

The custom design can then be edited in the default Unreal Engine UMG editor and set as a custom template in the slide tools.

### Advanced Presentation Functions
#### Update Slides
Update all slides can be used if a slide looks outdated, like if the format doesn’t fit the viewport size or the text on the slides is not representing the values of the details panel. This is just for the editor. When presenting the slides are updated automatically.

#### Fix Slide Numbers
Fix Slide Numbers can be used when slide indexes are not valid anymore like when a slide gets deleted that was in the middle of the presentation. The button basically packs the slide indexes back together.

### Navigation Functions
The navigation function can be used to find the slides in the game world.

### Exporting Presentation
Exporting Presentations are done like exporting games – just goto “File” -> “Package Project” -> “Target Platform”

### Presenting
Presentating is very simple – just use “Space”, “Right Arrow” or “Left Mouse” to go to the next slide or use “Backspace”, “Left Arrow” or “Right Mouse” to go back.

*The automatic configuration may not work in every project depending on the things that happen when the level loads. Basically, what needs to be done to get into presentation mode is to set the level-gamemode to be the PresentationMode and not override it at the start of the level.

