* I built the `soundPlayerExample` project provided with openFrameworks and inspected the source code
    * I learned how sounds are loaded and played and how to adjust their volume and speed
* I tried messing around with playing sounds myself
    * I downloaded a dice roll sound effect and put it in a `sounds` folder
    * Apparently the path passed to the `soundPlayer` is relative to the `data` folder which I could not locate
        * So I created one, but then found out it had to go in the `bin` folder
        * then I had a problem with git ignoring the sound file even though our `.gitignore` clearly has a rule to _not_ ignore the `data` folder (???), so I ended up just moving it back to a `sounds` folder in the root directory
    * Lo and behold I was able to play the dice sound effect through a mouse click and a button press
* I tried using `ofxGui` to create some GUI elements but I found it not so great so I instead began to play around with `ofxDatGui`
    * Learned how buttons work and how to register actions to them
* I found some dice stock images and managed to make them appear on screen with `ofImage`
* Managed to fix the `data` folder issue by writing my own `.gitignore`
* Went crawling back to `ofxGui` because I ended up not liking `ofxDatGui`
    * Made a row of toggles for keeping dice appear but they can't be clicked on for some reason
    * Fixed the clicking issue; ofxToggle.setup() needed to go in ofApp:setup() (who would've thunk it)
    * Made additional GUI elements for displaying score, displaying whether bonus has been earned, and rolling dice
    * Decided to have ofApp handle all GUI elements so I moved die image handling to ofApp instead of Die class

