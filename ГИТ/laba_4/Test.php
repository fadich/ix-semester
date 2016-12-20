<?php
namespace tests\codeception\unit\models;


use app\models\cashbox\CashBox;
use yii\codeception\TestCase;
use app\components\HelpClasses\ComponentHelper;

class Test extends TestCase
{
    /** @var CashBox $_cash */
    protected $_cash;

    /**
     * @dataProvider providerDepositCashBox
     *
     * @param $expectation
     * @param $value
     * @param $comment
     */
    public function testMe($expectation, $value, $comment)
    {
        ComponentHelper::clientDbConnectionInit(156, "DKCGJkLH_eGL");
        $this->_cash = new CashBox(132);
        $this->assertClassHasAttribute('value', CashBox::class);
        $this->assertClassHasAttribute('comment', CashBox::class);
        $this->assertEquals($expectation, $this->_cash->deposit(['value' => $value, 'comment' => $comment]));
//                echo "<pre>"; var_export($this->_cash->attributes); echo "</pre>";

        $this->assertEquals(true, true);
    }

    public function providerDepositCashBox()
    {
        return [
            [
                'expectation' => true,
                'value'       => 15.15,
                'comment'     => 'Comment',
            ],
            [
                'expectation' => true,
                'value'       => 150.15,
                'comment'     => 'Комментарий к пополнению',
            ],
            [
                'expectation' => false,     // Because the required comment (and it's length should be 3..155) and the value should be > 0.01
                'value'       => 0,
                'comment'     => '',
            ],
            [
                'expectation' => false,     // Because the value should be > 0.01
                'value'       => 15.9,
                'comment'     => '',
            ],
            [
                'expectation' => false,
                'value'       => 0,
                'comment'     => 'Comment',
            ],
            [
                'expectation' => false,     // Because the value should be < 9999999999
                'value'       => 99999999999,
                'comment'     => 'Comment',
            ],
            [
                'expectation' => false,     // Because the comment's length should be 3..155
                'value'       => 296.08,
                'comment'     => 'CommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentComment
                                  CommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentComment',
            ],
            [
                'expectation' => true,
                'value'       => (rand() * rand() / rand()) * rand(-1, 1),
                'comment'     => $this->generateRandomString(rand(0, 156)),
            ],
        ];
    }

    private function generateRandomString($len)
    {
        $str = '';
        while (strlen($str) < $len) {
            $str .= substr(md5(microtime()),rand(0,26),5);
        }
        return $str;
    }
}
