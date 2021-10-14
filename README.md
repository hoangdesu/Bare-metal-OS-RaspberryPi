# Bare metal OS on Raspberry Pi 3 Model B+

### Table of Contents
* [Project Description](#description)
    * [Version 1](#version1)
    * [Version 2](#version2) 
* [How to run project?](#run)
* [Acknowledgement](#acknowledgement)
* [Connect](#connect)

<a name="description"></a>
# Project Description
<!-- * My final project for EEET2481 - Embedded System Design and Implementation
* Whac-A-Mole style game with a mix of my favorite meme - BONK!
* Implemented for Nuvoton Nu-LB-NUC140 development board -->
This project includes 2 versions of bare metal operating systems for the Raspberry Pi 3 Model B+. Version 1 is more about interracting with the Rasp using UART and Mailbox, while Version deals more with the graphical interface.

<a name="version1"></a>
# Version 1
This version mainly uses the CLI to interract with the OS using the provided commands. Compile and run the image, type `help` to see all the available commands

<p align="center"><img src="./img/v1_help.jpg" alt="Welcome screen with help command" width="60%"></p>
<p align="center">Welcome screen with help command</p>

<p align="center"><img src="./img/v1_color.jpg" alt="Terminal text and background colors" width="60%"></p>
<p align="center">Set terminal text and background colors</p>

<p align="center"><img src="./img/v1_draw.jpg" alt="Draw graphic on screen" width="70%"></p>
<p align="center">Draw graphic on screen</p>


<a name="version2"></a>
# Version 2
This version concerns more about the Graphical User Interface, allowing the user to control what being displayed on screen, and even play a mini game called "Rescue the Pink-cess". Use the CLI to control the screen

<p align="center"><img src="./img/v2_main.jpg" alt="Welcome screen with text display" width="70%"></p>
<p align="center">Welcome screen with text display</p>

<p align="center"><img src="./img/v2_image.jpg" alt="Small image" width="70%"></p>
<p align="center">Display small image</p>

<p align="center"><img src="./img/v2_scroll.jpg" alt="Scrollable large image" width="70%"></p>
<p align="center">User can use WASD to scroll with large image</p>

<p align="center"><img src="./img/v2_cat.gif" alt="Playing video" width="40%"></p>
<p align="center">Pressing 4 will play this gif on QEMU screen</p>

<p align="center"><img src="./img/v2_game.jpg" alt="Scrollable large image" width="70%"></p>
<p align="center">Save the "Pink-cess" game</p>



<a name="run"></a>
# How to run project?




















### Game states
Welcome screen:

<img src="./screenshots/welcome.jpg" alt="Welcome screen" width="100%">

Tutorial:

<img src="./screenshots/tutorial.jpg" alt="Tutorial screen" width="70%">

Game play:

<img src="./screenshots/play.jpg" alt="Play screen" width="70%">

Gameover:

<img src="./screenshots/gameover.jpg" alt="Gameover" width="70%">


### Demo video
Watch on Youtube: 

[![Watch on Youtube!](https://img.youtube.com/vi/UcwJONlfsrk/hqdefault.jpg)](https://www.youtube.com/watch?v=UcwJONlfsrk)


### Program flowchart
<img src="./sprites/Flowchart.png" alt="Flowchart" width="80%">


<a name="run"></a>
# How to run project?
- Navigate to `src` folder
- Open the `Bonk.uvprojx` project in Keil uVision 5. It should look something like this:

<img src="./screenshots/keil.jpg" alt="Keil uVision5" width="90%">

- Build the project and upload it to your board


<a name="acknowledgement"></a>
# Acknowledgement
Tool for converting between images and byte arrays: https://javl.github.io/image2cpp/. Configure as below to display properly on LCD:
- Background color: Black
- Invert image colors: Yes
- Adjust brightness / alpha threshold to expectation
- Scaling: scale or stretch to fill canvas
- Center everything
- Code output format: plain bytes
- Draw mode: Vertical - 1 bit per pixel (since this LCD uses vertical scan)
- Generate code and benefit!

Also I'd like to send my thanks to my teammates Thuận, Trung, Triều for helping with this project. Fun story, this project was done during the heat of Corona pandemic in Ho Chi Minh city, where I didn't get to touch the board until the very last days. I paired up with 2 other guys who had the board, where I wrote the program and send it over to them to check pixel by pixel. Jeez it was a pain 😂. After nights of pair-programming in irritation, they finally managed to get the board deliver to me to fully work on the game. Finaly the product got shipped just an hour before the deadline =)) 


<a name="connect"></a>
# Connect with me
* My [Website](https://hoangdesu.com/)
* MY [LinkedIn](https://www.linkedin.com/in/hoangdesu/)
* My [Facebook](https://www.facebook.com/Hoangdayo/)
* My [Instagram](https://www.instagram.com/hoang.desu/)
* You can shoot me an [email](mailto:hoangdesu@gmail.com) too

If you find this project useful, you can let me know. I would love to hear about it!




