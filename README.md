---
add scale information when use ORB detector and descriptor

use pyramid operation and fuse the whole descriptors in all the layers.



for orb, [1] said:
> One of the issues that we have not adequately addressed here is scale invariance. Although we use a pyramid scheme for scale, we have not explored per keypoint scale from depth cues, tuning the number of octaves, etc.. Future work also includes GPU/SSE optimization, which could improve LSH by another order of magnitude.


Thus, this project losts its value if I still use multi-layer gaussian pyramid to fuse layers... This project will be used for coding training.

[1] Rublee E, Rabaud V, Konolige K, et al. ORB: An efficient alternative to SIFT or SURF[C]// IEEE International Conference on Computer Vision. IEEE, 2011:2564-2571.
