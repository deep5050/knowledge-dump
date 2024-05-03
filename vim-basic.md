| Command          | Description                                                                                     |
|------------------|-------------------------------------------------------------------------------------------------|
| `i`              | Switch to insert mode (before the cursor).                                                      |
| `a`              | Switch to insert mode (after the cursor).                                                       |
| `o`              | Open a new line below the current line and switch to insert mode.                                |
| `O`              | Open a new line above the current line and switch to insert mode.                                |
| `Esc`            | Exit insert mode and return to normal mode.                                                     |
| `:`              | Enter command-line mode.                                                                        |
| `w`              | Move forward one word.                                                                          |
| `b`              | Move backward one word.                                                                         |
| `gg`             | Move to the first line of the document.                                                         |
| `G`              | Move to the last line of the document.                                                          |
| `0`              | Move to the beginning of the line.                                                              |
| `$`              | Move to the end of the line.                                                                    |
| `dd`             | Delete the current line.                                                                        |
| `yy`             | Yank (copy) the current line.                                                                   |
| `p`              | Paste the contents of the clipboard below the cursor.                                           |
| `P`              | Paste the contents of the clipboard above the cursor.                                           |
| `u`              | Undo the last change.                                                                           |
| `Ctrl+r`         | Redo the last undone change.                                                                    |
| `:q`             | Quit Vim (if no unsaved changes).                                                               |
| `:w`             | Save the current file.                                                                          |
| `:wq`            | Save the current file and quit Vim.                                                             |
| `:q!`            | Quit Vim without saving changes.                                                                |
| `:e filename`    | Open a new file named `filename`.                                                               |
| `:sp filename`   | Split the window horizontally and open `filename` in the new window.                             |
| `:vsp filename`  | Split the window vertically and open `filename` in the new window.                               |
| `Ctrl+w` + `w`   | Switch between windows.                                                                         |
| `Ctrl+w` + `q`   | Close the current window.                                                                       |
| `Ctrl+w` + `s`   | Split the window horizontally.                                                                  |
| `Ctrl+w` + `v`   | Split the window vertically.                                                                    |
| `vimdiff file1 file2` | Open Vim with two files (`file1` and `file2`) in diff mode.                                         |
| `:diffsplit file` | Open `file` in a new split window and enter diff mode.                                             |
| `]c`            | Jump to the next change.                                                                         |
| `[c`            | Jump to the previous change.                                                                     |
| `:diffupdate`   | Refresh the diff view to reflect any changes made to the files.                                    |
| `:diffoff!`     | Toggle off diff mode, converting the splits back to normal editing mode.                           |
| `:diffget`      | Get changes from the other buffer (replace current buffer's content with changes from the other buffer). |
| `:diffput`      | Put changes into the other buffer (replace other buffer's content with changes from the current buffer). |
| `:diffg RE`     | Get changes from a specific revision (use `RE` to specify a revision number).                      |
| `:diffput RE`   | Put changes into a specific revision (use `RE` to specify a revision number).                      |
