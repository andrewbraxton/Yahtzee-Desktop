* I built the `soundPlayerExample` project provided with openFrameworks and inspected the source code.
    * I learned how sounds are loaded and played and how to adjust their volume and speed
* I tried messing around with playing sounds myself.
    * I downloaded a dice roll sound effect and put it in a `sounds` folder
    * Apparently the path passed to the `soundPlayer` is relative to the `data` folder which I could not locate
        * So I created one, but then found out it had to go in the `bin` folder
        * then I had a problem with git ignoring the sound file even though our `.gitignore` clearly has a rule to _not_ ignore the `data` folder (???), so I ended up just moving it back to a `sounds` folder in the root directory
    * Lo and behold I was able to play the dice sound effect through a mouse click and a button press
