Cashew
========

[![Build Status](https://travis-ci.org/billhsu/cashew.png)](https://travis-ci.org/billhsu/cashew)
[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/billhsu/cashew?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Freestyle 3D sketching app.  
The only limit is your imagination.  

Website: [http://billhsu.github.io/cashew](http://billhsu.github.io/cashew)  
Demo Video: On [YouTube](https://www.youtube.com/watch?v=kX9W6WuJf5U), or on [优酷](http://v.youku.com/v_show/id_XMTQ0NzcwODQwOA==.html)

<a href="http://billhsu.github.io/cashew"><img src="doc/screenshot.png" width="600" /></a>

## Install
1. Download latest version of cashew from: [https://github.com/billhsu/cashew/releases/download/v1.0/cashew.dmg](https://github.com/billhsu/cashew/releases/download/v1.0/cashew.dmg)
2. Open `cashew.dmg` and drag `cashew.app` to `Applications`

## Usage
### File
<p><img src="doc/button_document_new.png" width="30px" style="margin:5px;" align="middle"/>Create a new sketch file</p>
<p><img src="doc/button_document_open.png" width="30px" style="margin:5px;" align="middle"/>Open a sketch file</p>
<p><img src="doc/button_document_save.png" width="30px" style="margin:5px;" align="middle"/>Save the current sketch file</p>

### Operations
<p><img src="doc/button_standard_view.png" width="30px" style="margin:5px;" align="middle"/>Reset camera to recommended angle</p>
<p><img src="doc/button_movecenter.png" width="30px" style="margin:5px;" align="middle"/>Translate camera position</p>
<p><img src="doc/button_pencil.png" width="30px" style="margin:5px;" align="middle"/>Toggle between drawing straight lines or free drawing</p>
<p><img src="doc/button_undo.png" width="30px" style="margin:5px;" align="middle"/>Undo last operation</p>
<p><img src="doc/button_redo.png" width="30px" style="margin:5px;" align="middle"/>Redo last operation</p>
<p><img src="doc/button_delete.png" width="30px" style="margin:5px;" align="middle"/>Delete lines</p>
<p><img src="doc/button_mirror.png" width="30px" style="margin:5px;" align="middle"/>Select mirror mode</p>


## Build
### With command line(Mac OS)
```shell
./configure && make
xctool -project Xcode/cashew/cashew.xcodeproj -scheme cashew build;
```
### With Xcode
1. ```./configure && make```
2. Open Xcode/cashew/cashew.xcodeproj with Xcode

## Author
**Shipeng Xu**

+ http://BillHsu.me
+ http://twitter.com/1991bill
+ http://weibo.com/billhsu
