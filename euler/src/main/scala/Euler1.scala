
object Euler1 {

  def euler1(n : Int): Int = {
    (1 until n).filter {
      k => k % 3 == 0 || k % 5 == 0
    }.sum
  }

  def euler2(limit: Int): Int = {
    limit
  }

  def main(args: Array[String]): Unit = {
    println(euler1(1000))
  }
}
