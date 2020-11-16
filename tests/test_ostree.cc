#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

#include "ostree/repo.h"

class OSTreeTest : public ::testing::Test {
 protected:
  OSTreeTest(){
  }

  virtual void SetUp() {
    path_ = mkdtemp(const_cast<char*>((testing::TempDir() + "OSTreeTest-repo-XXXXXX").c_str()));
    repo_ = OSTree::Repo::create(path_);
  }

  virtual void TearDown() {
    boost::filesystem::remove_all(path_);
  }

  bool isRepoInited() const {
    return boost::filesystem::exists(path_ + "/config") && boost::filesystem::exists(path_ + "/objects");
  }

 protected:
  std::string path_;
  OSTree::Repo::Ptr repo_;
};


TEST_F(OSTreeTest, CreateDestroy) {
  ASSERT_TRUE(isRepoInited());
}

TEST_F(OSTreeTest, InitExistingDestroy) {
  ASSERT_TRUE(isRepoInited());
  OSTree::Repo repo_from_filesystem(path_);
}

TEST_F(OSTreeTest, AddRemote) {
  ASSERT_TRUE(isRepoInited());
  repo_->addRemote("treehub", "http://localhost", "", "", "");
}

TEST_F(OSTreeTest, Pull) {
  ASSERT_TRUE(isRepoInited());
  repo_->addRemote("treehub", "http://localhost:8787", "", "", "");
  repo_->pull("treehub", "test");
}

TEST_F(OSTreeTest, Checkout) {
  ASSERT_TRUE(isRepoInited());
  repo_->addRemote("treehub", "http://localhost:8787", "", "", "");
  repo_->pull("treehub", "test");
  const std::string dir_to_checkout_to = mkdtemp(const_cast<char*>((testing::TempDir() + "OSTreeTest-folder-XXXXXX").c_str()));
  try {
    repo_->checkout("test", "/", dir_to_checkout_to);
  } catch (const std::exception& exc) {

  }

  const auto expected_file = std::string(dir_to_checkout_to) + "/test.file";
  ASSERT_TRUE(boost::filesystem::exists(expected_file));

  boost::filesystem::remove_all(dir_to_checkout_to);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}