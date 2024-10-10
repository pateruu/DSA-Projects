# DSA-Projects
Projects using Data Structures and Algorithm principles.
_____________________________________________________________________________

This repository contains my projects and implementations from my **Data Structures and Algorithms Course**. Each project focuses on implementing efficient data structures and algorithms in C++, with practical applications to real-world problems.

## Table of Contents
- [Project1: Music Playlist](#project-1-music-playlist)
- [Project2: What Time Is It, Big-Bad Wolf?](#project-2-what-time-is-it-big-bad-wolf)
- [Project3: Spell-Checker](#project-3-spell-checker)
- [Project4: Tokenizing](#project-4-tokenizing)
- [Project5: Emergency Response](#project-5-emergency-response)


---

## Project 1: Music Playlist

- **Project Overview**: Created a C++ program to manage a playlist of songs where users can add, play, and delete songs from an array-based playlist.
- **Data Structures Used**: 
  - `Array`: Used to store the playlist of songs.
  - `Custom Classes`: Defined for the songs' title and artist.
  - `Input/Output Handling`: Managed via standard input and output streams (`cin`/`cout`).

---

## Project 2: What Time Is It, Big-Bad Wolf?

- **Project Overview**: Implemented a modified children's game where players move toward a "wolf" on a 2D plane. The game tracks player movements and determines who gets caught.
- **Data Structures Used**: 
  - `Doubly Linked List`: Used to store and update players' positions and maintain the game state.
  - `Custom Node Class`: Each node stores player coordinates.

---

## Project 3: Spell-Checker

- **Project Overview**: Developed a spell-checker that stores a dictionary of words and suggests corrections for misspelled words using a prefix tree (Trie).
- **Data Structures Used**: 
  - `Trie (Prefix Tree)`: Efficiently stores the dictionary of words for fast look-up and auto-suggestion.
  - `Node Structure`: Each node represents a letter in the word with a 26-ary branching factor.

---

## Project 4: Tokenizing

- **Project Overview**: Implemented a tokenization system that converts words to numeric tokens and vice versa for large-scale AI text processing.
- **Data Structures Used**: 
  - `Hash Table`: Used to map words to tokens for efficient lookup.
  - `Array`: Maps tokens back to words.
  - `Resizable Array`: Dynamically resizes based on load factor to maintain performance.

---

## Project 5: Emergency Response

- **Project Overview**: Built a graph representing a city's road network for emergency response routing. Dijkstra’s algorithm is used to calculate the shortest path between intersections.
- **Data Structures Used**: 
  - `Graph (Adjacency List)`: Represents intersections as vertices and roads as weighted edges.
  - `Hash Map`: Efficiently maps nodes (intersections) to their edges (roads).
  - `Priority Queue`: Used to implement Dijkstra’s algorithm.

---
