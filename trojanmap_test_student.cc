#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapStudentTest, Test1) {
  TrojanMap m;
  // Test the simple case
  auto names = m.Autocomplete("Ch");
  std::unordered_set<std::string> gt = {"Chinese Street Food", "Chevron 2", "Chucks Chicken & Waffles", "Cheebos Burger", "Chase", "Church of Christ", "Chevron", "Chipotle", "Chase Plaza Heliport", "Chevron 1", "Chick-fil-A"}; // groundtruth for "Ch"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());

  // Test the lower and upper case
  names = m.Autocomplete("cH"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());

  // Test the no result case
  names = m.Autocomplete("cho"); 
  gt = {};
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}

TEST(TrojanMapStudentTest, Test2) {
  TrojanMap m;
  // Test Ralphs
  auto position = m.GetPosition("Chinese Street Food");
  std::pair<double, double> gt1(34.0244847, -118.2840326); // groundtruth for "Chinese Street Food"
  EXPECT_EQ(position, gt1);
  // Test Unknown
  position = m.GetPosition("CHOa");
  std::pair<double, double> gt2(-1, -1);
  EXPECT_EQ(position, gt2);
  // Test empty
  position = m.GetPosition("");
  std::pair<double, double> gt3(-1, -1);
  EXPECT_EQ(position, gt3);
}

