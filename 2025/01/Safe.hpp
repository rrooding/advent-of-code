#pragma once

class Safe {
 private:
  int dialPosition_{50};
  int numberOfZerosLandings_{0};
  int numberOfZeroPasses_{0};

  [[nodiscard]] static int clampDialPosition(int position) {
    return ((position % 100) + 100) % 100;
  }

 public:
  void turnLeft(int ticks) {
    int newPosition = dialPosition_ - ticks;

    if (newPosition <= 0 && dialPosition_ > 0) {
      // We pass through 0 from a positive position
      numberOfZeroPasses_++;
    }

    if (newPosition < 0) {
      // Count additional wraps beyond the first 0
      numberOfZeroPasses_ += (-newPosition) / 100;
    }

    dialPosition_ = clampDialPosition(newPosition);

    if (dialPosition_ == 0) {
      numberOfZerosLandings_++;
    }
  }

  void turnRight(int ticks) {
    int newPosition = dialPosition_ + ticks;

    // Count how many times we pass through 0
    numberOfZeroPasses_ += newPosition / 100;

    dialPosition_ = clampDialPosition(newPosition);

    if (dialPosition_ == 0) {
      numberOfZerosLandings_++;
    }
  }

  [[nodiscard]] int dialPosition() const { return dialPosition_; }

  [[nodiscard]] int getNumberOfZeroLandings() const {
    return numberOfZerosLandings_;
  }

  [[nodiscard]] int getNumberOfZeroPasses() const {
    return numberOfZeroPasses_;
  }
};