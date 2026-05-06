"""
Data verification and physics checking
"""
from __future__ import annotations
import typing
from . import covariance
__all__: list[str] = ['TestStatus', 'covariance']
class TestStatus:
    """
    The test status
    
    Members:
    
      Success
    
      Warning
    
      Fail
    
      Skipped
    """
    Fail: typing.ClassVar[TestStatus]  # value = <TestStatus.Fail: 2>
    Skipped: typing.ClassVar[TestStatus]  # value = <TestStatus.Skipped: 3>
    Success: typing.ClassVar[TestStatus]  # value = <TestStatus.Success: 0>
    Warning: typing.ClassVar[TestStatus]  # value = <TestStatus.Warning: 1>
    __members__: typing.ClassVar[dict[str, TestStatus]]  # value = {'Success': <TestStatus.Success: 0>, 'Warning': <TestStatus.Warning: 1>, 'Fail': <TestStatus.Fail: 2>, 'Skipped': <TestStatus.Skipped: 3>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
