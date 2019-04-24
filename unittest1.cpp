#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AiStrD_4.2/Map.h"
#include "../AiStrD_4.2/Map.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_forLab2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(insert_all_new_correct_insert)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			Assert::IsTrue(map.get_root()->key == 5 && map.get_root()->right->key == 7 &&
				map.get_root()->left->key == 2 && map.get_root()->value == 34 &&
				map.get_root()->right->value == 90 && map.get_root()->left->value == 78);
		}

		TEST_METHOD(insert_try_to_insert_same_key_value_not_change)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(2, -5);
			Assert::IsTrue(map.get_root()->key == 5 && map.get_root()->right->key == 7 &&
				map.get_root()->left->key == 2 && map.get_root()->value == 34 &&
				map.get_root()->right->value == 90 && map.get_root()->left->value == 78);
		}

		/*************************************************************************************************************
	    1.Each node is either red or black.
	    2.The root is black. (This rule is sometimes omitted.)
	    3.All leaves are black.
	    4.If a node is red, then both its children are black.
	    5.Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
        ***************************************************************************************************************/

		TEST_METHOD(insert_root_is_black_only_leaves_are_red)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			Assert::IsTrue(!map.get_root()->isRed  && map.get_root()->right->isRed && map.get_root()->left->isRed);
		}

		TEST_METHOD(insert_change_node_color_for_propertie_5)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(0, 56);
			Assert::IsTrue(!map.get_root()->isRed && !map.get_root()->right->isRed && 
				!map.get_root()->left->isRed && map.get_root()->left->left->isRed);
		}

		TEST_METHOD(insert_rightRotate)  
		{
			Map<int, int> map;
			map.insert(9, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			Assert::IsTrue(map.get_root()->key==7  && map.get_root()->right->key==9 && map.get_root()->left->key==2);
		}

		TEST_METHOD(insert_leftRotate)
		{
			Map<int, int> map;
			map.insert(9, 34);
			map.insert(17, 90);
			map.insert(22, 78);
			Assert::IsTrue(map.get_root()->key == 17 && map.get_root()->right->key == 22 && map.get_root()->left->key == 9);
		}

		TEST_METHOD(remove_root_only_root)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.remove(5);
			Assert::IsTrue(map.get_root()== nullptr);
		}

		TEST_METHOD(remove_root_root_have_a_child)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.remove(5);
			Assert::IsTrue(map.get_root()->key == 7);
		}

		TEST_METHOD(remove_node_without_child)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.remove(2);
			Assert::IsTrue(map.get_root()->key == 5 && map.get_root()->right->key == 7 &&
				map.get_root()->left == nullptr );
		}

		TEST_METHOD(remove_node_with_one_child)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(1, -5);
			map.remove(2);
			//map.insert(3, 80);

			Assert::IsTrue(map.get_root()->key == 5 && map.get_root()->right->key == 7 &&
				map.get_root()->left->key == 1 ); 
		}

		TEST_METHOD(remove_left_node_with_both_child)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(1, -5);
			map.insert(3, 444);
			map.remove(2);
			//map.insert(3, 80);

			Assert::IsTrue(map.get_root()->key == 5 && map.get_root()->right->key == 7 &&
				map.get_root()->left->key == 1 && map.get_root()->value == 34 &&
				map.get_root()->right->value == 90 && map.get_root()->left->value == -5);
		}

		TEST_METHOD(remove_right_node_with_both_child)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(9, -5);
			map.insert(6, 444);
			map.remove(7);
			//map.insert(3, 80);

			Assert::IsTrue(map.get_root()->key == 5 && map.get_root()->right->key == 6 &&
				map.get_root()->left->key == 2 && map.get_root()->value == 34 &&
				map.get_root()->right->value == 444 && map.get_root()->left->value == 78);
		}

		TEST_METHOD(destruct_delete_tree)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(9, -5);
			map.insert(6, 444);
			map.~Map();
			//map.insert(3, 80);

			Assert::IsTrue(map.get_root() == nullptr);
		}

		TEST_METHOD(findNode_contains)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(9, -5);
			map.insert(6, 444);
			

			Assert::IsTrue(map.findNode(2)->key==2 && map.findNode(2)->value==78);
		}

		TEST_METHOD(findNode_not_contains)
		{
			Map<int, int> map;
			map.insert(5, 34);
			map.insert(7, 90);
			map.insert(2, 78);
			map.insert(9, -5);
			map.insert(6, 444);
			

			Assert::IsTrue(map.findNode(25) == nullptr);
		}

	};
}