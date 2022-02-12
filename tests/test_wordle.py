import unittest
import wordle

class TestWordle(unittest.TestCase):
    def test_check_rule(self):
        test_data_list = [
            ("ultra", "aback", "YWWWW", True),
            ("paste", "tooth", "WWWGW", True),
            ("ultra", "tutor", "WYGWY", True),
        ]

    def test_calc_rule_type(self):
        test_data_list = [
            ("ultra", "aback", "YWWWW"),
            ("paste", "tooth", "WWWGW"),
            ("ultra", "tutor", "WYGWY"),
        ]
        for test_data in test_data_list:
            actual = wordle.calc_rule_type(test_data[0], test_data[1])
            self.assertEqual(actual, test_data[2])

if __name__ == "__main__":
    unittest.main()
