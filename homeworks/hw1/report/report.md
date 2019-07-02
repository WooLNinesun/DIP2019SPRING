---
export_on_save:
  phantomjs: "pdf"
---

# Digital Image Processing 2019 Spring
<p style="text-align:right;">B04902083 Hsiang-Hsu Chuang</p>

## WARM-UP: SIMPLE MANIPULATIONS
暖身題目，將照片翻轉然後做 power law。

### images
@import "./image/p0_01.png" {width="100%"}

### Discussion of results
圖片中的 power law 參數 p 是 1.2，當 p 越大，會變越亮，反之則變暗。因為原圖沙地的地方普遍偏淡，所以想調高對比讓沙地明顯一點，調整後覺得 1.2 最合適！太高的話後面的燈塔會變得太亮而不好看。

<!-- pagebreak -->
## PROBLEM 1: IMAGE ENHANCEMENT
調整圖片的亮度，然後做 global and local histogram equalization 並比較差別。

### Discussion of results

@import "./image/p1_01.png" {width="100%"}
@import "./image/p1_02.png" {width="100%"}

首先是將亮度除 2 和 除 3 的結果以及它們的 histogram，可以看到亮度降低整個 histogram 都往左邊靠了。

<!-- pagebreak -->
@import "./image/p1_03.png" {width="100%"}
@import "./image/p1_04.png" {width="100%"}

再來是對除 2 和 除 3 的結果做 global histogram equalization，因為原本兩張圖都偏暗，所以做完 global histogram equalization 後整體亮度都會提升。

<!-- pagebreak -->
@import "./image/p1_05.png" {width="100%"}
@import "./image/p1_06.png" {width="100%"}

再來是對除 2 和 除 3 的結果做 local histogram equalization，時間上因為 window 開 51 * 51 pixels，所以跑比較久，但整體感覺上比 global histogram equalization 的結果要好很多，不會太亮。

### Difference between local and global

在結果上感覺 global histogram equalization 會因為極端偏暗而產出來的 CDF 不會是很好的線性，而 local histogram equalization，彌補了這點！

<!-- pagebreak -->
## PROBLEM 2: NOISE REMOVAL

給一張原圖和兩張不同 noise 特徵的圖片，挑選適合的 noise filter 來去除 noise

### Origin image

@import "./image/p2_01.png" {width="100%"}

### Discussion of results

實作了三種 noise filer:
1. low pass filter
    @import "./image/p2_02.png" {width="100%"}
    
    這種 filter 對 3(b) 的效果較好，因為 3(c) 的 noise 屬於 pluse noise，效果沒這麼顯著。
    > p3_N1 PSNR:28.534432
    > p3_N2 PSNR:22.389400

<!-- pagebreak -->
2. outlier detection
    @import "./image/p2_03.png" {width="100%"}

    這種相對其他兩個 filter，去除 noise 的效果沒這個好，且因為平均的關係，整張圖的亮度也跟著變暗。3(c) 的 pluse noise 有淡化，但還是很明顯。

    > p3_N1 PSNR:14.102354
    > p3_N2 PSNR:13.270323

3. median filtering
    @import "./image/p2_04.png" {width="100%"}

    這種 filter 對 3(c) 的效果比其他兩個要好很多，pluse noise 基本上看不太到了，對 3(b) 的效果也不錯，但還是覺得 low pass filter 要好一點。意外的兩張 PSNR 結果一樣！

    > p3_N1 PSNR:27.916136
    > p3_N2 PSNR:27.916136

整體來說，對 3(b) 的 Uniform noise 來說，low pass filter 效果最好，對 3(c) 的 pluse noise 來說 median filtering 的效果遠比其他兩個好！

## Note:
histogram 的產生方式是使用 python 的 matplotlib 和 numpy，使用 jupyter 來當顯示界面，jupyter export 的 html 檔為 homework1.html
