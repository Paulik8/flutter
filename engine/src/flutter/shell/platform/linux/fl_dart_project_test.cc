// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/shell/platform/linux/public/flutter_linux/fl_dart_project.h"
#include "gtest/gtest.h"

#include <gmodule.h>

TEST(FlDartProjectTest, GetPath) {
  g_autoptr(FlDartProject) project =
      fl_dart_project_new("/projects/my_dart_project");
  EXPECT_STREQ(fl_dart_project_get_path(project), "/projects/my_dart_project");
}

TEST(FlDartProjectTest, GetPathRelative) {
  g_autoptr(FlDartProject) project = fl_dart_project_new("foo");
  g_autofree gchar* exe_path = g_file_read_link("/proc/self/exe", nullptr);
  ASSERT_TRUE(exe_path != nullptr);
  g_autofree gchar* dir = g_path_get_dirname(exe_path);
  g_autofree gchar* expected_path = g_build_filename(dir, "foo", nullptr);
  EXPECT_STREQ(fl_dart_project_get_path(project), expected_path);
}

TEST(FlDartProjectTest, GetAssetsPath) {
  g_autoptr(FlDartProject) project =
      fl_dart_project_new("/projects/my_dart_project");
  g_autofree gchar* assets_path = fl_dart_project_get_assets_path(project);
  EXPECT_STREQ(assets_path, "/projects/my_dart_project/flutter_assets");
}

TEST(FlDartProjectTest, GetIcuDataPath) {
  g_autoptr(FlDartProject) project =
      fl_dart_project_new("/projects/my_dart_project");
  g_autofree gchar* assets_path = fl_dart_project_get_icu_data_path(project);
  EXPECT_STREQ(assets_path, "/projects/my_dart_project/icudtl.dat");
}
