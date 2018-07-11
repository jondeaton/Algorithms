/* Here is presented a particularly breif solution to 
 * the "how much water does this histogram hold" problem, written in scala. 
 */

import math._

def water(heights: Seq[Int]): Int = {
	val leftHighest = heights.scanLeft(0)(max)
	val rightHightest = heights.scanRight(0)(max)
	heights.zip(leftHighest.zip(rightHightest)).map(t => {
		val (h, (l, r)) = t
		val w = min(l, r) - h
		if (w > 0) w else 0
	}).sum
}

