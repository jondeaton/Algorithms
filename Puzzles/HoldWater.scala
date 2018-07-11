/* Here is presented a particularly breif solution to 
 * the "how much water does this histogram hold" problem, written in scala. 
 */

import math._

def water(heights: Seq[Int]): Int = {
	val leftMax = heights.scanLeft(0)(max)
	val rightMax = heights.scanRight(0)(max)
	(heights, leftMax, rightMax).zipped.map(t => {
		val (h, l, r) = t
    	max(0, min(l, r) - h)
	}).sum
}
