| Command                   | Description                                                                                       |
|---------------------------|---------------------------------------------------------------------------------------------------|
| `:find filename`          | Open a file named `filename` in the current directory or its subdirectories.                      |
| `:grep pattern **/*.c`    | Search for `pattern` recursively in all `.c` files in the current directory and its subdirectories. |
| `:vimgrep /pattern/ **/*.c` | Similar to `:grep`, but opens the results in a quickfix window for easier navigation.              |
| `:cnext`                  | Move to the next entry in the quickfix window (results from `:grep` or `:vimgrep`).                 |
| `:cprev`                  | Move to the previous entry in the quickfix window.                                                 |
| `:cfirst`                 | Move to the first entry in the quickfix window.                                                    |
| `:clast`                  | Move to the last entry in the quickfix window.                                                     |
| `:copen`                  | Open the quickfix window to navigate through search results.                                        |
| `gd`                      | Go to the local declaration of the variable under the cursor.                                      |
| `gD`                      | Go to the global declaration of the identifier under the cursor.                                   |
| `Ctrl+]`                  | Jump to the definition of the identifier under the cursor (using ctags).                            |
| `Ctrl+t`                  | Jump back to the previous location (using ctags).                                                   |
| `Ctrl+w` + `}`             | Increase the height of the current window.                                                         |
| `Ctrl+w` + `{`             | Decrease the height of the current window.                                                         |
| `Ctrl+w` + `>`             | Increase the width of the current window.                                                          |
| `Ctrl+w` + `<`             | Decrease the width of the current window.                                                          |
| `:ls`                     | List all open buffers.                                                                            |
| `:bnext`                  | Switch to the next buffer.                                                                         |
| `:bprev`                  | Switch to the previous buffer.                                                                     |
| `:bfirst`                 | Switch to the first buffer.                                                                        |
| `:blast`                  | Switch to the last buffer.                                                                         |
| `Ctrl+]`                  | Jump to the definition of the identifier under the cursor (using ctags).                            |
| `Ctrl+t`                  | Jump back to the previous location (after using `Ctrl+]`).                                           |
| `:tag tagname`            | Jump to the definition of `tagname` (using ctags).                                                   |
| `:tag` + `Tab`            | Auto-complete available tags.                                                                      |
| `Ctrl+w` + `gf`           | Open the file under the cursor in a new tab.                                                        |
| `Ctrl+w` + `s`            | Split the window horizontally.                                                                     |
| `Ctrl+w` + `v`            | Split the window vertically.                                                                       |
| `Ctrl+w` + `w`            | Switch between windows in a split.                                                                  |
| `Ctrl+w` + `r`            | Rotate windows upwards (changing their positions).                                                  |
| `Ctrl+w` + `x`            | Swap the current window with the next one.                                                          |
| `Ctrl+w` + `o`            | Close all other windows, keeping only the active one.                                               |
| `:set hidden`             | Allow Vim to keep multiple buffers open without requiring them to be saved or closed.               |
| `:Explore`                | Open a file explorer window to navigate through the directory structure.                             |
| `:cd path/to/directory`   | Change Vim's current working directory to `path/to/directory`.                                       |
| `:Gstatus`                | Open a Git status window to view changes and navigate through modified files (requires Git plugin). |
| `:Gblame`                 | Open a Git blame window to see the commit history of the current file (requires Git plugin).        |
| `:Gdiff`                  | Open a Git diff window to view changes made to the current file (requires Git plugin).               |
| `:help keyword`           | Open Vim's built-in help documentation for `keyword`.                                               |
| `K`                       | Look up the keyword under the cursor in Vim's built-in help.                                         |
| `Ctrl+]`                  | Jump to the definition of the identifier under the cursor (using ctags).                            |
| `Ctrl+t`                  | Jump back to the previous location (after using `Ctrl+]`).                                           |
| `g]`                      | List all the references to the keyword under the cursor.                                             |
| `gR`                      | Rename the variable under the cursor (requires vim-r plugin).                                        |
| `gf`                      | Open the file under the cursor in a new tab.                                                        |
| `gF`                      | Open the file under the cursor in a new split window.                                                |
| `:grep pattern **/*.c`    | Search for `pattern` recursively in all `.c` files in the current directory and its subdirectories. |
| `:Ggrep pattern`          | Search for `pattern` recursively in the current Git repository.                                      |
| `:vimgrep /pattern/ **/*.c` | Search for `pattern` recursively in all `.c` files and open results in a quickfix window.           |
| `:cn`                     | Move to the next entry in the quickfix list.                                                        |
| `:cp`                     | Move to the previous entry in the quickfix list.                                                    |
| `:cc`                     | Display information about the current entry in the quickfix list.                                    |
| `:copen`                  | Open the quickfix window to navigate through search results.                                         |
