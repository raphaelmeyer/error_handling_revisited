# Half Demo

## Setup

Split screen in two
- editor showing `demo.hs`
- console for `ghci`

Start ghci and load code:

    stack exec ghci

    > :load demo.hs

## half function

    half :: Int -> Int
    half n = div n 2


    > :reload

    > half 4
    > half 5

    > half ( half 8 )
    > half ( half ( half 18 ))

## Slides

## odd/even

    half :: Int -> Maybe Int
    half n | even n     = Just ( div n 2 )
           | otherwise  = Nothing


    > :reload

    > half 8
    > half 9

    > half ( half 16 )

## Slides

## bind

    > half 16
    > half 16 >>= half
    > half 16 >>= half >>= half

    > half 20
    > half 20 >>= half
    > half 20 >>= half >>= half
