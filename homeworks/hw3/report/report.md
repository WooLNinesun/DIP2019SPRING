---
export_on_save:
  phantomjs: "pdf"
---

# Digital Image Processing 2019 Spring
<p style="text-align:right;">B04902083 Hsiang-Hsu Chuang</p>

## PROBLEM 1
### Discussion of results
  @import "./images/0004.png"

  1. boundary extraction 照著講義上的公式寫 code，沒有特別的難，有把作業 2 的 edge detect 比較，結果沒有差太多，但缺點就是只能用在 binary 的圖片上。

  2. 不同的物件要上不同的顏色，因為是灰階圖，所以不太明顯，我採用的方式是遍歷整張圖，發現有 255 的值，就做 BFS 上色，會這樣做是發現講義上的公式仔細想想就可以發現和 BFS 等價。

  3. thinning 和 skeletonizing 基本上就是照著同影片和課本做，做兩次查表，不斷縮小到沒有任何 pixel 會被刪除後停止。觀察可以發現 skeletonizing 比 thinning 多了一些線段表示原本的骨架。

<!-- pagebreak -->
## PROBLEM 2:
### Discussion of results
  @import "./images/0002.png"

  這題因為 k-means 做法寫都有問題，就放棄寫 k-means 的部分，寫了 Law’s method 得部分後拿去和 low-pass & high-pass 做比較，和上課說的一樣，第 0 張圖和 low-pass 出來的圖一樣，第 8 張圖和  high-pass 出來的圖一樣。

<!-- pagebreak -->
## BONUS
### Discussion of results
  @import "./images/0005.png"

  這題我的做法是先做 1st_order 找出 edge，並調整 threshold，因為後面會接 close 的操作，所以把 threshold 調的高一點讓圖片的邊騷為沒有連起來，之後再用 close 連接邊，這樣 berries 就會變成中間剩下一點點黑色，且黑色不和其他 berries 相連。最後反轉顏色做 shrinking，讓 berries 只剩下一點。但因為 reverse 的影響，會出現大片白色區域，最後解法是點必須是獨立，8 個方向都沒有其他的點在才算成一個 berries。

  這樣的算法最後算出來是 130，已經是我嘗試的做法裡最接近的了...

