
import org.scalatest._

class EulerSpec extends FlatSpec with Matchers {

  "The Euler1 object" should "solve 10" in {
    Euler1.euler1(10) shouldEqual 23
  }

}
