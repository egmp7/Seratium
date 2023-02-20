# Seratium

Seratium is a DJ application capable of reading .mp3 and .wav files, with DJ controllers allowing tempo and volume manipulation. The user also has access to a playlist that let's add music to the desks.

<br>

![Seratium](Assets/Seratium.png)

# Install Seratium IOS

Download and install the [Seratium Package](https://github.com/egmp7/Seratium/releases/download/music/Seratium.pkg).

# Source Hierarchy

This is the herachy applied in the program

1. main.cpp
    - MainComponent
        - PLayer 1
        - PLayer 2
        - MainGUI
            - DeckGUI 1
                - DeckAnimation
                - TimeTracker
                - WaveformDisplay
                - currentTime
                - Volume
                    - FaderLookAndFeel
                - Speed
                    - FaderLookAndFeel
                - currentTime
            - DeckGUI 2
                - DeckAnimation
                - TimeTracker
                - WaveformDisplay
                - Volume
                    - FaderLookAndFeel
                - Speed
                    - FaderLookAndFeel
                - currentTime
            - Playlist
            - Crossfader
2. CSV (Static)
3. Format (Static)
4. TrackEntry (Model)

