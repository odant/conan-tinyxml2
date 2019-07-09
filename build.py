# minizip Conan package
# Dmitriy Vetutnev, ODANT, 2019


import platform, os
from conan.packager import ConanMultiPackager


# Common settings
username = "odant" if "CONAN_USERNAME" not in os.environ else None
# Windows settings
visual_versions = ["15"] if "CONAN_VISUAL_VERSIONS" not in os.environ else None
visual_runtimes = ["MD", "MDd", "MT", "MTd"] if "CONAN_VISUAL_RUNTIMES" not in os.environ else None
with_unit_tests = True if "WITH_UNIT_TESTS" in os.environ else False


def add_with_unit_tests(builds):
    result = []
    for settings, options, env_vars, build_requires, reference in builds:
        options["tinyxml2:with_unit_tests"] = with_unit_tests
        result.append([settings, options, env_vars, build_requires, reference])
    return result

def filter_libcxx(builds):
    result = []
    for settings, options, env_vars, build_requires, reference in builds:
        if settings["compiler.libcxx"] == "libstdc++11":
            result.append([settings, options, env_vars, build_requires, reference])
    return result


if __name__ == "__main__":
    builder = ConanMultiPackager(
        username=username,
        visual_versions=visual_versions,
        visual_runtimes=visual_runtimes,
        exclude_vcvars_precommand=True
    )
    builder.add_common_builds(pure_c=False, shared_option_name=False)
    # Adjusting build configurations
    builds = builder.items
    if platform.system() == "Linux":
        builds = filter_libcxx(builds)
    builds = add_with_unit_tests(builds)
    # Replace build configurations
    builder.items = []
    for settings, options, env_vars, build_requires, _ in builds:
        builder.add(
            settings=settings,
            options=options,
            env_vars=env_vars,
            build_requires=build_requires
        )
    builder.run()
