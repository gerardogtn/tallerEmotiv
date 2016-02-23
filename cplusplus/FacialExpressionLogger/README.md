# Facial Expression Logger

Simple example that logs to console the facial expression data of an
Emotiv Epoc device. The data logged is: isBlinking, isLeftWinking, isRightWinking,
areEyesOpen, areEyesClosed, surprisePower, frownPower, smilePower, and clenchPower.

## 'Power' variables

The power variables simply represent the certainty that an Emotiv User is doing
an action. For instance the surprisePower indicates from [0, 1] the degree of
certainty that a user is surprised. It is worth noting that Emotiv Engine can
only detect either surprise xor frown and smile xor clench. This means that if
we detect a frown gesture, the emotiv will not detect a surprise gesture and
viceversa. 

## Code basics

We need two basic types of variables: EmoEngineEventHandle and EmoStateHandle.
The EmoEngineEventHandle retrieves the events received by the Emotiv Engine (so
    that you can filter by the events that are relevant to you); and the
EmoStateHandle represents an actual Emotiv State as retrieved from an event and
from which you can obtain raw data.
