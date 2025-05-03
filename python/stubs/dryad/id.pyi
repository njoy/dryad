"""
Identifiers for particles, elements, etc.
"""
from __future__ import annotations
import typing
__all__ = ['ElementID', 'LevelID']
class ElementID:
    """
    The element identifier
    """
    def __eq__(self, arg0: ElementID) -> bool:
        ...
    def __ge__(self, arg0: ElementID) -> bool:
        ...
    def __gt__(self, arg0: ElementID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, number: int) -> None:
        """
        Initialise the element identifier
        
        Arguments:
            self     the identifier
            number   the element number
        """
    @typing.overload
    def __init__(self, number: str) -> None:
        """
        Initialise the reaction
        
        Arguments:
            self     the identifier
            symbol   the element symbol, name or alternative name
        """
    def __le__(self, arg0: ElementID) -> bool:
        ...
    def __lt__(self, arg0: ElementID) -> bool:
        ...
    def __ne__(self, arg0: ElementID) -> bool:
        ...
    @property
    def name(self) -> str:
        """
        The element name
        """
    @property
    def number(self) -> int:
        """
        The element number
        """
    @property
    def symbol(self) -> str:
        """
        The element symbol
        """
class LevelID:
    """
    The level identifier
    """
    continuum: typing.ClassVar[int] = 150
    def __eq__(self, arg0: LevelID) -> bool:
        ...
    def __ge__(self, arg0: LevelID) -> bool:
        ...
    def __gt__(self, arg0: LevelID) -> bool:
        ...
    def __hash__(self) -> int:
        """
        Hash function
        """
    @typing.overload
    def __init__(self, level: int) -> None:
        """
        Initialise the level identifier
        
        Arguments:
            self     the identifier
            number   the level number
        """
    @typing.overload
    def __init__(self, level: str) -> None:
        """
        Initialise the level identifier
        
        Arguments:
            self     the identifier
            symbol   the level symbol
        """
    def __le__(self, arg0: LevelID) -> bool:
        ...
    def __lt__(self, arg0: LevelID) -> bool:
        ...
    def __ne__(self, arg0: LevelID) -> bool:
        ...
    @property
    def number(self) -> int:
        """
        The level number
        """
    @property
    def symbol(self) -> str:
        """
        The level symbol
        """
