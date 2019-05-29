---
title: Error Handling *Revisited*
; author: Raphael Meyer
patat:
  theme:
    codeBlock: [onVividWhite, dullBlack]
...

     _____                       _   _                 _ _ _
    | ____|_ __ _ __ ___  _ __  | | | | __ _ _ __   __| | (_)_ __   __ _
    |  _| | '__| '__/ _ \| '__| | |_| |/ _` | '_ \ / _` | | | '_ \ / _` |
    | |___| |  | | | (_) | |    |  _  | (_| | | | | (_| | | | | | | (_| |
    |_____|_|  |_|  \___/|_|    |_| |_|\__,_|_| |_|\__,_|_|_|_| |_|\__, |
                                                                   |___/
    
    
    
    
    
    
    
                                    ____            _      _ __           __
                                   / __ \___ _   __(_)____(_) /____  ____/ /
                                  / /_/ / _ \ | / / / ___/ / __/ _ \/ __  /
                                 / _, _/  __/ |/ / (__  ) / /_/  __/ /_/ /
                                /_/ |_|\___/|___/_/____/_/\__/\___/\__,_/

---

Error handling 🤔

. . .

Taking care of side effects 👍

---

```cpp
void do_homing() {
  table->x()->poweroff();
  table->y()->poweroff();
  table->x()->home(Homing::NegativeLimit);
}
```

```haskell
do_homing :: Table -> IO ()
do_homing table = do
    let x = getX table
        y = getY table
    powerOff x
    powerOff y
    home x NegativeLimit
```

---

# Error Handling ?

Side Effects ( Handling )

          __    __
         / /_  / /_ _   __
        / __ \/ __ \ | / /
       / /_/ / /_/ / |/ /
      /_.___/_.___/|___/

      Making Visions Work

