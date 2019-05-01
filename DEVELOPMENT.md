* I built the `soundPlayerExample` project provided with openFrameworks and inspected the source code
    * I learned how sounds are loaded and played and how to adjust their volume and speed
* I tried messing around with playing sounds myself
    * I downloaded a dice roll sound effect and put it in a `sounds` folder
    * Apparently the path passed to the `soundPlayer` is relative to the `data` folder which I could not locate
        * So I created one, but then found out it had to go in the `bin` folder
        * then I had a problem with git ignoring the sound file even though our `.gitignore` clearly has a rule to _not_ ignore the `data` folder (???), so I ended up just moving it back to a `sounds` folder in the root directory
            * fixed this problem by writing my own `.gitignore`
    * Lo and behold I was able to play the dice sound effect through a mouse click and a button press
* I tried using `ofxGui` to create some GUI elements but I found it not so great so I instead began to play around with `ofxDatGui`
    * Learned how buttons work and how to register actions to them
* I found some dice stock images and managed to make them appear on screen with `ofImage`
* Went crawling back to `ofxGui` because I ended up not liking `ofxDatGui`
    * Made a row of toggles for keeping dice appear but they can't be clicked on for some reason
        * Fixed the clicking issue; ofxToggle.setup() needed to go in ofApp:setup() (who would've thunk it)
    * Made additional GUI elements for displaying score, displaying whether bonus has been earned, and rolling dice
    * Decided to have ofApp handle all GUI elements so I moved die image handling to ofApp instead of Die class
    * Began working on adding the scoring categories to the GUI, ended up having to sketch my interface on paper to figure out how to best position things on the screen
* Entire window seems to have an issue with padding
    * Padding factor I added to compensate not working
    * Hitboxes for the scoring categories are wonky
    * Kind of fixed this by turning off window border but now the window will have to be unmovable as well as unresizable
* Began working on the game logic
    * Actual game logic was surprisingly simple, the difficult parts were figuring out the best data structures to use (good thing this isn't CS 225 yet), working with the arcane STL functions (why can you not call .contains() on a map???), and working out the logic of when GUI elements should enable/disable
    * Originally had all of my element enabling/disabling in listener functions but realized the logic was becoming difficult to parse and having it scattered everywhere was annoying
        * Moved all of it to `ofApp::update()` and the code is now much more organized and understandable
    * Cleaned up and implemented some remaining minor pieces of logic: joker rules, Yahtzee bonuses, and starting a new game
* Lastly, put the finishing touches on visual improvements (fonts, text padding, etc.), code style, and documentation