# Half Demo

## Setup

Split screen in two

- editor showing `demo.hs`
- console for `ghci`

Start ghci and load code:

    stack exec ghci

    > :load demo.hs

## Demo

### Slides

-> Maybe

### half function

code:

    half :: Int -> Int
    half n = div n 2

repl:

    > :reload

    > half 4
    > half 5
    > half 7

    > half ( half 8 )
    > half ( half ( half 18 ))

### Slides

-> `data Maybe a = Nothing | Just a`

### odd/even

code:

    half :: Int -> Maybe Int
    half n | even n     = Just ( div n 2 )
           | otherwise  = Nothing

repl:

    > :reload

    > half 8
    > half 9

    > half ( half 16 )

### Slides

-> `instance Monad Maybe where` ...

### bind

    > half 16
    > half 16 >>= half
    > half 16 >>= half >>= half

    > half 18
    > half 18 >>= half
    > half 18 >>= half >>= half
