"""
Identifiers for particles, elements, etc.
"""
from __future__ import annotations
import typing
__all__ = ['ElementID']
class ElementID:
    """
    The element identifier, with associated element symbol, name and aliases
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
            self     the reaction
            number   the element number
        """
    @typing.overload
    def __init__(self, number: str) -> None:
        """
        Initialise the reaction
        
        Arguments:
            self     the reaction
            symbol   the element symbol or name
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
