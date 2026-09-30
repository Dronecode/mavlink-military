---
layout: home

hero:
  name: MAVLink-M
  tagline: An open MAVLink 2 dialect for coordination and situational awareness between uncrewed platforms and command systems.
  actions:
    - theme: brand
      text: Introduction
      link: /en/index.md
    - theme: brand
      text: Messages
      link: /en/messages/military.md
    - theme: brand
      text: Getting Started
      link: /en/getting_started/index.md
    - theme: alt
      text: Source (GitHub)
      link: https://github.com/Dronecode/mavlink-military

features:
  - title: Built on MAVLink 2
    details: Includes common.xml and drops into any MAVLink 2 stack. Generate bindings with the standard mavgen tooling.
  - title: Shared vocabulary
    details: Tracks, positions, taskings, status, and structured reports that cooperating systems can all read.
  - title: Gateway friendly
    details: Messages are shaped to translate cleanly into the command-and-control standards those systems already run on.
  - title: Clear boundaries
    details: Carries intent and observation. Device-internal configuration stays off the wire by design.
---
