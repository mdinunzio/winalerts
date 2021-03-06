from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

__version__ = "0.0.2"


ext_modules = [
    Pybind11Extension("winalerts",
        ["winalerts.cpp"],
        define_macros = [('VERSION_INFO', __version__)],
        ),
]

setup(
    name="winalerts",
    version=__version__,
    author="Michael DiNunzio",
    author_email="mdinunzio@gmail.com",
    url="https://github.com/mdinunzio/winalerts",
    description="A module providing and interface for Windows alerts.",
    long_description="",
    ext_modules=ext_modules,
    zip_safe=False,
    python_requires=">=3.6",
)