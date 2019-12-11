# C++ Errorhandling Revisited

In order to do something useful or at least interesting, any software has to interact with the world in some way. But sometimes these interactions do not yield the desired results. Something might go wrong. There will be errors. Put differently, we have to cope with side effects.

When I started to learn Haskell, I was fascinated by the way the language deals with side effects. In functional programming you generally do not want to have side effects. But it is an inevitable fact that you still have to. This necessity resulted in very elegant concepts that recently gained a lot of attention in conventional programming languages as well.

In this talk we will explore how error handling might look in Haskell, how it influenced other languages and what we can learn therefrom. We will look at how to apply this to C++ and touch a few features of C++17. But we'll also see where the available language constructs prevent us from going further.

## Elevator Pitch

This talk is a unique introduction to Haskell. Motivated by a C++ implementation problem, I will teach some core aspects of monads without using the m-word.
