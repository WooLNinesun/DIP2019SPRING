---
export_on_save:
  phantomjs: "pdf"
---

# Digital Image Processing 2019 Spring
<p style="text-align:right;">B04902083 Hsiang-Hsu Chuang</p>

## PROBLEM 1
### Discussion of results
  @import "./images/0001.png"

  1. edge detection:
    使用之前寫的 canny edge detection 生 edge map，發現 gussion 開太強會把大樓頂端的線條模糊掉導致偵測不到，但開太弱的話會有像是大樓裡面的電燈被偵測出來。最後我覺得最好的參數是 gussion simga = 0.4, low_threshold = 5, high_threshold = 50。
  
  2. accumulator array as a new image:
    對每個偵測出來的邊的點為基點，每個角度的線都轉到 Hough 上去，最後形成 H1。
  
  3. contrast adjustment:
    直接使用 global histogram equalize 做 contrast adjustmen，效果不錯。
  
  4. draw the top 10 and top 20 significant lines:
    將 accumulator array 的每一格丟進 priority_queue 裡面做排序，然後 pop 出前幾個數值最大的畫線（color = 128）在圖上。發現有幾條和原本的 edge map 一樣，但也有幾條算出來的誤差相當大...

  5. pros and cons
  * props:
      * 比較不會受到影像的 noise 影響
      * 可以偵測在線有一些斷裂的情況下偵測出這條線>
  * cons:
      * 如果今天有一條線本來就是斷的，Hough 會讓他們連起來。
