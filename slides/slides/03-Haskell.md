# more code

```haskell
foo :: Maybe Int
foo = Just 42

bar :: Int -> Maybe Int
bar x = x / 0

main = do
    x <- foo
    y <- bar x
    return ( x + y )
```

