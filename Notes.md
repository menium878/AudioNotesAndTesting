## 1
Analog to digital conversion - taking the analog source coverted to numbers


What is a sound? Vibration waves

Human hearing 20hz and 20khz

Wave values between -1 and 1
### Sampling Rate
Rate at which is sound is being sampled
44100/sec
time-> x axis
signal get sampled 44100 each sec

sampled -> hold (hold that value to next time point now its 1/44100s)



### Bit depth
if i have the values between -1 and 1 i have 2^x of spaces between them where x is a bit depth value
### Quantization
Process of placing the value sampled closses to availble bit depth posssition

### Nyquist theory

Max representable frequentensy 1/2 of your sampled rate

so 44100/2 = 22050 hz it fit our whole range of hearing into itself

## 2
### Aliasing
The frequentensy that we are hearing

when we go from 0 to 22050 aka Nyquist we have true value but then it goes down from top to 0 (for 44100)

## 3
### sine wave
Any sound could be broken doing into series of the sine waves of diffrent frequentensy amplitute etc.

Single pick on fundamental frequentensy

---- Side Note -----
squere note multiple harmonices with one pick
--------------------

Fourier
Any periodic signal (like a repeating sound wave) can be expressed as the sum of sine and cosine waves of different frequencies, amplitudes, and phases.

In other words, even a very complex sound (like music or speech) can be broken down into a collection of pure tones (simple sine waves).

## Side topic
### PCM vs Compressed Formats
#### PCM - Pulse-code Modulation
Raw way of representing digital audio
taking analog wave mesasuring its amplitude at regular intervals(sample rate) and storinging this numbers

PCM all about accuracy - WAV and AIFF files are usally PCM inside a container

#### Compressed Formats
##### Lossless Compression
keeps alll the original PCM data but packs it more efficiently
FLAC ALAC
When decoded getting bacvk original PCM
30%-60% spaced saved
